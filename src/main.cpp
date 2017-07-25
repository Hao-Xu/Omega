#include "classManager/taskManager.h"

int main(int argc, char *argv[]) {

taskManager *tasks = new taskManager;

//tasks->print();
tasks->initialize(argc, argv);
//tasks->assemble();
//tasks->run();
tasks->postProcess();
//tasks->~taskManager();

taskManager * task2 ;
{
task2 = new taskManager(3);
}
task2->print();
delete tasks;

return 0;
}
