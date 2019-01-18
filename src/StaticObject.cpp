/**
  *   @file StaticObject.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source code for StaticObject
  */

#include "../include/StaticObject.hpp"

namespace pe {

  // Empty constructor
  StaticObject::StaticObject(): PhysicsObject() {}

  // Constructor
  StaticObject::StaticObject(Shape* shape):
  PhysicsObject(shape, 0.f, true, ObjectType::StaticObject) {}

}// end of namespace pe