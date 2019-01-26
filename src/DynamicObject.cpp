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

  // setForce implementation
  void DynamicObject::setForce(Vector2f force) {
    force *= physics.inverse_mass; // acceloration caused by the force
    physics.acceloration = physics.acceloration + force;
  }

  // setVelocity implementation
  void DynamicObject::setVelocity(Vector2f velocity) {
    physics.velocity = velocity;
  }

  // collisionAction implementation
  void DynamicObject::collisionAction(Vector2f position_change) {
    if (dotProduct(physics.velocity, position_change) > 0.f) {
      // position change should be in the inverse direction
      physics.position -= position_change;
    }
    else {
      physics.position += position_change;
    }
    physics.velocity.update(0.f, 0.f);
    physics.acceloration.update(PhysicsProperties::GravityX, PhysicsProperties::GravityY);
  }

}// end of namespace pe
