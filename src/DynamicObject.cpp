/**
  *   @file DynamicObject.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source code for DynamicObject
  */


#include "../include/DynamicObject.hpp"

namespace pe {

  // Empty constructor
  DynamicObject::DynamicObject(): PhysicsObject() {}

  // Constructor
  DynamicObject::DynamicObject(Shape *shape, float density):
  PhysicsObject(shape, density, false, ObjectType::DynamicObject) {}

}// end of namespace pe
