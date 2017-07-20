#include "taskManager.h"
#include "materialManager.h"

using namespace tinyxml2;
void taskManager::print() {
    std::cout << " print " << std::endl; 
}

void taskManager::initialize(int &argc, char ** &argv) {

MPI_Status stat;
// initialize MPI  
MPI_Init(&argc,&argv);

// get number of tasks 
MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

// get my rank 
  
MPI_Comm_rank(MPI_COMM_WORLD,&rank);

switch(rank) {      
    case 0:
        printf ("Started!\n");
	//std::ofstream fstrm;
	//std::ifstream finput;
        //finput.open(argv[1]);
        //finput >> E0 >> Poisson0 >> a1 >> a2 >> a3 >> a4;
        //finput >> C0 >> C1 >> alpha >> Debug >> fd0;
        printf ("My rank= %d\n", rank);
	//std::cout << " E0= " << E0 <<" " << " fd0= " << fd0 << std::endl;  
        int inputI;
 	for (int i = 0; i < argc; i++) {
            if (strcmp("-i", argv[i]) == 0) {
		  //inputFile = argv[i + 1];  
		  inputI = i;
	    }  
	    //std::cout << " argv[" << i << "] = " << argv[i] << std::endl;
        }
	//std::cout << " inputFile = " << inputFile << std::endl;
	//std::cout << " TEST = " << TEST << std::endl;
	XMLDocument xmlDoc;
	XMLError eResult = xmlDoc.LoadFile(argv[inputI+1]);
        //XMLCheckResult(eResult);
	break;
}



// this one is obvious  
MPI_Get_processor_name(hostname, &len);
//printf ("Number of tasks= %d My rank= %d Running on %s\n", numtasks,rank,hostname);
std::string materialName = "elastic";
materialManager * materials = new materialManager(materialName);
delete materials;
elementList.push_back(new elementManager());
// do some work with message passing 


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
