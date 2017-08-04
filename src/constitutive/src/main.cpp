//#include <iostream>
//#include <unordered_map>
//#include <functional>
#include <vector>
#include "material.h"
#include "materialFactory.h"

int main(int argc, char *argv[])
{
  std::vector<material*> shapes;

  shapes.push_back( materialFactory::instantiate("isotropicElastic") );
  shapes.push_back( materialFactory::instantiate("Square") );
  shapes.push_back( materialFactory::instantiate("Ellipse") );

  //material * p = materialFactory::instantiate("isotropicElastic");
  //p->draw(); 
  //p->printVariables();
  //shapes[0]->printVariables();
  //shapes[0]->draw();
  for (auto& shape: shapes){
    //shape->draw();
    //shape->printVariables();
  }
  for (auto& shape: shapes){
    delete shape;
    //shapes.erase(shape);
  }
  //delete p;
  //delete [] shapes;
  //delete shapes[2];
  //delete shapes[1];
  //delete shapes[0];
  shapes.clear();
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

