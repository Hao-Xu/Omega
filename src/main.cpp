#include "mpi.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char *argv[]) {
int  numtasks, rank, len, rc; 
char hostname[MPI_MAX_PROCESSOR_NAME];
double E0, Poisson0, a1, a2, a3, a4, C0, C1, alpha, Debug,fd0;     

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
        ofstream fstrm;
        ifstream finput;
        finput.open(argv[1]);
        finput >> E0 >> Poisson0 >> a1 >> a2 >> a3 >> a4;
        finput >> C0 >> C1 >> alpha >> Debug >> fd0;
        printf ("My rank= %d\n", rank);
        cout << " E0= " << E0 <<" " << " fd0= " << fd0 << endl;  
        for (int i = 0; i < argc; i++) {
            cout << " argv[" << i << "] = " << argv[i] << endl;
                     }
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
