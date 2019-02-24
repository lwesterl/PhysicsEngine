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

  // updatePhysics implementation
  void DynamicObject::updatePhysics(float elapsed_time) {
    // apply gravity to the object
    float delta_x = physics.velocity.getX() * elapsed_time +
    (physics.acceloration.getX() + PhysicsProperties::GravityX) * elapsed_time * elapsed_time;
    float delta_y = physics.velocity.getY() * elapsed_time +
    (physics.acceloration.getY() + PhysicsProperties::GravityY) * elapsed_time * elapsed_time;
    physics.movePosition(Vector2f(delta_x, delta_y));
    // decrease acceloration and velocity based on physics.resistance_factor
    physics.applyResistance(elapsed_time);
  }

}// end of namespace pe
