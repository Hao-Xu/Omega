//#include <iostream>
//#include <unordered_map>
//#include <functional>
#include <vector>
#include "classLib/material.h"
#include "classLib/materialFactory.h"

int main(int argc, char *argv[])
{
  std::vector<material*> shapes;

  shapes.push_back( materialFactory::instantiate("isotropicElastic") );
  shapes.push_back( materialFactory::instantiate("Square") );
  shapes.push_back( materialFactory::instantiate("Ellipse") );

  material * p = materialFactory::instantiate("isotropicElastic");
  p->draw(); 
  p->printVariables();
  //shapes[0]->printVariables();
  //shapes[0]->draw();
  for (auto& shape: shapes){
    //shape->draw();
    //shape->printVariables();
  }
  /* expectd output:
  Registering class 'Circle'
  Registering class 'Square'
  Registering class 'Ellipse'
  drawing a circle 
  drawing a square 
  drawing an ellipse
  */

  return 0;
}

