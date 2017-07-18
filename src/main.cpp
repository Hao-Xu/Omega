#include "mpi.h"
#include "tinyxml2/tinyxml2.h"
#include "taskManager/taskManager.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#ifndef XMLCheckResult
	#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { printf("Error: %i\n", a_eResult); return a_eResult; }
#endif

//using namespace std;
using namespace tinyxml2;

int main(int argc, char *argv[]) {
int  numtasks, rank, len, rc; 
char hostname[MPI_MAX_PROCESSOR_NAME];
double E0, Poisson0, a1, a2, a3, a4, C0, C1, alpha, Debug,fd0;     
std::string inputFile;
/*

*/       
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
	std::ofstream fstrm;
	std::ifstream finput;
        finput.open(argv[1]);
        finput >> E0 >> Poisson0 >> a1 >> a2 >> a3 >> a4;
        finput >> C0 >> C1 >> alpha >> Debug >> fd0;
        printf ("My rank= %d\n", rank);
	std::cout << " E0= " << E0 <<" " << " fd0= " << fd0 << std::endl;  
        int inputI;
 	for (int i = 0; i < argc; i++) {
            if (strcmp("-i", argv[i]) == 0) {
		  inputFile = argv[i + 1];  
		  inputI = i;
	    }  
	    std::cout << " argv[" << i << "] = " << argv[i] << std::endl;
        }
	std::cout << " inputFile = " << inputFile << std::endl;
	XMLDocument xmlDoc;
	XMLError eResult = xmlDoc.LoadFile(argv[inputI+1]);
        XMLCheckResult(eResult);
	taskManager tasks;// = new taskManager();
        tasks.print();
	break;
}

// this one is obvious  
MPI_Get_processor_name(hostname, &len);
printf ("Number of tasks= %d My rank= %d Running on %s\n", numtasks,rank,hostname);


// do some work with message passing 


// done with MPI  
MPI_Finalize();

return 0;
}
