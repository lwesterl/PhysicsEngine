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

  // setForce override
  void DynamicObject::setForce(Vector2f force) {
    force *= physics.inverse_mass; // acceloration caused by the force
    physics.acceloration = physics.acceloration + force;
  }

  // setVelocity override
  void DynamicObject::setVelocity(Vector2f velocity) {
    physics.velocity = velocity;
  }

}// end of namespace pe
