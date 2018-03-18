#include "classManager/taskManager.h"

int main(int argc, char *argv[]) {

taskManager *tasks = new taskManager;

//tasks->print();
tasks->initialize(argc, argv);
//tasks->assemble();
tasks->run();
tasks->postProcess();
//tasks->~taskManager();

delete tasks;
std::cout << " Simulation is completed." << std::endl;
return 0;
}
