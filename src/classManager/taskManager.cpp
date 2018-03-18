#include "taskManager.h"

using namespace tinyxml2;

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

// Test function
void taskManager::print() {
    std::cout << " print " << mm << std::endl; 
}

// Initialize the problem
void taskManager::initialize(int &argc, char ** &argv) {

  MPISetup(argc, argv);

  getOptions(argc, argv);

  readXML(argc, argv); 

  //printf ("Started!\n");
  //printf ("My rank= %d\n", rank);

  delete materialList[0];

}

void taskManager::MPISetup(int &argc, char ** &argv) {

  MPI_Status stat;
  // initialize MPI  
  MPI_Init(&argc,&argv);

  // get number of tasks 
  MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

  // get my rank 
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);

  // this one is obvious  
  MPI_Get_processor_name(hostname, &len);
  printf ("Number of tasks= %d My rank= %d Running on %s\n", numtasks,rank,hostname);

  // do some work with message passing 
} 

void taskManager::getOptions(int & argc, char ** &argv) {

  int c;
  int digit_optind = 0;
  while (1) {
    int this_option_optind = optind ? optind : 1;
    int option_index = 0;
    static struct option long_options[] = {
      {"add",     required_argument, 0,  0 },
      {"append",  no_argument,       0,  0 },
      {"delete",  required_argument, 0,  0 },
      {"verbose", no_argument,       0,  0 },
      {"create",  required_argument, 0, 'c'},
      {"file",    required_argument, 0,  0 },
      {"help",    no_argument,       0, 'h'},
      {"input",   required_argument, 0, 'i'},
      {0,         0,                 0,  0 }
    };

    c = getopt_long(argc, argv, "abc:d:h:i:012",
                 long_options, &option_index);
    if (c == -1)
      break;

    switch (c) {
      case 0:
        printf("option %s", long_options[option_index].name);
          if (optarg)
            printf(" with arg %s", optarg);
          printf("\n");
          break;

      case '0':
      case '1':
      case '2':
        if (digit_optind != 0 && digit_optind != this_option_optind)
          printf("digits occur in two different argv-elements.\n");
        digit_optind = this_option_optind;
        printf("option %c\n", c);
        break;

      case 'a':
        printf("option a\n");
        break;

      case 'b':
        printf("option b\n");
        break;

      case 'c':
        printf("option c with value '%s'\n", optarg);
        break;

      case 'd':
        printf("option d with value '%s'\n", optarg);
        break;

      case 'h':
        printf("option h with value '%s'\n", optarg);
        break;

      case 'i':
        inputFile = optarg; 
        printf("Input file: '%s'\n", optarg);
        break;

      case '?':
        break;

      default:
        printf("?? getopt returned character code 0%o ??\n", c);
    }
  }

  if (optind < argc) {
    printf("non-option ARGV-elements: ");
    while (optind < argc)
      printf("%s ", argv[optind++]);
      printf("\n");
  }
}

int taskManager::readXML(int &argc, char ** &argv) {

  XMLDocument xmlDoc;
  const char * szAttributeText = nullptr;
  XMLError eResult = xmlDoc.LoadFile(inputFile);
  printf("Reading XML file: '%s'\n", inputFile);
  XMLCheckResult(eResult);
  //
  XMLNode * pRoot = xmlDoc.FirstChild();

  if (pRoot == nullptr) {
    std::cout << "Input XML file is empty.\n" << std::endl;    
    return XML_ERROR_FILE_READ_ERROR;
  }
  //const char* title = xmlDoc.FirstChildElement("Root")->GetText();
  //const char* title = xmlDoc.FirstChildElement("Root")->Name();
  const char* title = xmlDoc.FirstChild()->Value();
  //const char* title = pRoot->FirstChildElement("IntValue")->Name();
  //XMLText * title = xmlDoc.FirstChild()->ToText();
  //std::cout << "<" << title << ">" << std::endl;

  // IntValue
  XMLElement * pElement = pRoot->FirstChildElement("IntValue");
  if (pElement) {
    int iOutInt;
    eResult = pElement->QueryIntText(&iOutInt);
    XMLCheckResult(eResult);

    XMLNode * pNode = pRoot->FirstChild();
    title = pNode->Value();
  } else {
     //return XML_ERROR_PARSING_ELEMENT;
  }

  // FloatValue
  pElement = pRoot->FirstChildElement("FloatValue");
  if (pElement != nullptr) {

    float fOutFloat;
    eResult = pElement->QueryFloatText(&fOutFloat);
    XMLCheckResult(eResult);
    //pNode = pNode->NextSibling();
    //title = pNode->Value();
    //std::cout << "title = <" << title << ">" << fOutFloat << std::endl;
  } else {
     //return XML_ERROR_PARSING_ELEMENT;
  }

  // Date
  pElement = pRoot->FirstChildElement("Date");
  if (pElement != nullptr) {

    int iOutDay, iOutYear;

    eResult = pElement->QueryIntAttribute("day", &iOutDay);
    XMLCheckResult(eResult);

    eResult = pElement->QueryIntAttribute("year", &iOutYear);
    XMLCheckResult(eResult);

    //pNode = pNode->NextSibling();
    //title = pNode->Value();

    szAttributeText = pElement->Attribute("month");
    if (szAttributeText == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
    std::string strOutMonth = szAttributeText;

    szAttributeText = pElement->Attribute("dateFormat");
    if (szAttributeText == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
    std::string strOutFormat = szAttributeText;

  } else {
     //return XML_ERROR_PARSING_ELEMENT;
  }

  // Mesh information
  pElement = pRoot->FirstChildElement("mesh");
  if (pElement == nullptr) {
    std::cerr << " No mesh provided" << std::endl; 
    return XML_ERROR_PARSING_ELEMENT;
  }

  //pNode = pNode->NextSibling();
  //title = pNode->Value();

  XMLElement * pListElement = pElement->FirstChildElement("external");

  if (pListElement) {
    const char * szMeshFile = nullptr;
    szMeshFile = pListElement->Attribute("inputFile");
    if (szMeshFile == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
  }

  pListElement = pElement->FirstChildElement("internal");
  if (pListElement) {
    XMLElement * pListChildElement = pListElement->FirstChildElement("node");
    title = pListChildElement->Name();
    std::cout << "node test ==== " << title << std::endl;
    int iOutValue;
    eResult = pListChildElement->QueryIntText(&iOutValue);
    std::cout << " node coordinate reads as " << iOutValue << std::endl;
    std::cout << " value " << pListChildElement->NextSibling()->Value() << std::endl;
    std::cout << " node coordinate reads as " << iOutValue << std::endl;
  } 
  
  // Materil parameters
  pElement = pRoot->FirstChildElement("material");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

  szAttributeText = pElement->Attribute("name");
  if (szAttributeText == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
  std::string strMaterialName = szAttributeText;
  materialName = szAttributeText;
  materialList.push_back(materialFactory::instantiate(materialName));
  std::cout << "size in readXML =" << materialList.size()-1 << std::endl;
  materialList[materialList.size()-1]->draw();

  szAttributeText = pElement->Attribute("domainSet");
  if (szAttributeText == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
  std::string strDomainSet = szAttributeText;
  //std::cout << " domainSet = " << strDomainSet << std::endl;

  //pNode = pNode->NextSibling();
  //title = pNode->Value();

  pListElement = pElement->FirstChildElement("parameter");

  float fOutYoung, fOutPoisson;
  eResult = pListElement->QueryFloatAttribute("young", &fOutYoung);
  XMLCheckResult(eResult);

  eResult = pListElement->QueryFloatAttribute("poisson", &fOutPoisson);
  XMLCheckResult(eResult);


  // Boundary conditions
  pElement = pRoot->FirstChildElement("boundaryCondition");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

  pListElement = pElement->FirstChildElement("Item");
  std::vector<int> BCList;

  XMLNode * pChildNode = pElement->FirstChild();
  const char * titleChild = pChildNode->Value();

  while (pListElement != nullptr) {
    int iOutBCid;

    const char * sOutType = nullptr;
    const char * sOutDomainSet = nullptr;
    float fOutValue;
    eResult = pListElement->QueryFloatAttribute("value", &fOutValue);
    XMLCheckResult(eResult);

    eResult = pListElement->QueryIntAttribute("id", &iOutBCid);
    XMLCheckResult(eResult);
    
    sOutType = pElement->Attribute("type");
    if (sOutType == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
    std::string strBCType = sOutType;

    sOutDomainSet = pElement->Attribute("domainSet");
    if (sOutDomainSet == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
    std::string strBCDomainSet = sOutDomainSet;


    BCList.push_back(iOutBCid);
    pListElement = pListElement->NextSiblingElement("Item");
  }

  // Loads
  pElement = pRoot->FirstChildElement("load");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

  pListElement = pElement->FirstChildElement("Item");
  std::vector<int> LoadList;

  pChildNode = pElement->FirstChild();
  titleChild = pChildNode->Value();

  while (pListElement != nullptr) {
    int iOutLoadid;
    const char * sOutType = nullptr;
    const char * sOutDomainSet = nullptr;
    float fOutValue;

    eResult = pListElement->QueryFloatAttribute("value", &fOutValue);
    XMLCheckResult(eResult);

    eResult = pListElement->QueryIntAttribute("id", &iOutLoadid);
    XMLCheckResult(eResult);
    
    sOutType = pElement->Attribute("type");
    if (sOutType == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
    std::string strBCType = sOutType;

    sOutDomainSet = pElement->Attribute("domainSet");
    if (sOutDomainSet == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
    std::string strBCDomainSet = sOutDomainSet;

    LoadList.push_back(iOutLoadid);
    pListElement = pListElement->NextSiblingElement("Item");
  }

  // Solver
  pElement = pRoot->FirstChildElement("solver");
  if (pElement == nullptr) return XML_ERROR_PARSING_ELEMENT;

  szAttributeText = pElement->Attribute("name");
  if (szAttributeText == nullptr) return XML_ERROR_PARSING_ATTRIBUTE;
  std::string strSolverName = szAttributeText;


  // List
  pElement = pRoot->FirstChildElement("List");
  if (pElement != nullptr) {

    pListElement = pElement->FirstChildElement("Item");
    std::vector<int> vecList;

    pChildNode = pElement->FirstChild();
    titleChild = pChildNode->Value();

    while (pListElement != nullptr) {
      int iOutListValue;
      eResult = pListElement->QueryIntText(&iOutListValue);
      XMLCheckResult(eResult);

      vecList.push_back(iOutListValue);
      pListElement = pListElement->NextSiblingElement("Item");
    }
  } else {
     //return XML_ERROR_PARSING_ELEMENT;
  }

  xmlDoc.SaveFile("./inputCheck.xml");

  return 0; 
}

void taskManager::assemble() {

}

void taskManager::run() {

}

void taskManager::postProcess() {
  while (!elementList.empty()) {
    elementList.pop_back();
  }
  

  MPI_Finalize();

}
