#include "classManager/taskManager.h"

int main(int argc, char *argv[]) {

taskManager *tasks = new taskManager;

//tasks->print();
tasks->initialize(argc, argv);
//tasks->assemble();
//tasks->run();
tasks->postProcess();
//tasks->~taskManager();
delete tasks;

return 0;
}
