#include "taskManager.h"

using namespace tinyxml2;
void taskManager::print() {
    std::cout << " print " << mm << std::endl; 
}

void taskManager::initialize(int &argc, char ** &argv) {

MPISetup(argc, argv);

getOptions(argc, argv);

printf ("Started!\n");
printf ("My rank= %d\n", rank);
//XMLDocument xmlDoc;
//XMLError eResult = xmlDoc.LoadFile(argv[inputI+1]);
//XMLCheckResult(eResult);

std::string materialName = "isotropicElastic";
printf ("material1\n");
materialList.push_back(materialFactory::instantiate(materialName));
printf ("material2\n");
materialList[0]->draw();
printf ("material3\n");
materialList[0]->printVariables();
printf ("material4\n");
delete materialList[0];
// do some work with message passing 

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

    c = getopt_long(argc, argv, "abc:d:i:012",
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
            printf("option d with value '%s'\n", optarg);
            break;

       case 'i':
	    inputFile = optarg; 
            printf("Input file: '%s'\n", optarg);
	    std::cout << "Input file: " << inputFile << std::endl;
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

void taskManager::readXML(int &argc, char ** &argv) {

}

void taskManager::assemble() {

}

void taskManager::run() {

}

void taskManager::postProcess() {
while (!elementList.empty())
{
    elementList.pop_back();
}

MPI_Finalize();

}
