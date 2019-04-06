/**
  *   @file DynamicObject.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source code for DynamicObject
  */


#include "../include/DynamicObject.hpp"
#include <iostream>

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
    // move DynamicObject to inverse direction to counter collision
    Vector2f direction_unit_vector = Vector2f(ABS(inverse_direction.getX()), ABS(inverse_direction.getY()));
    direction_unit_vector.normalize();
    physics.position += direction_unit_vector * position_change * collision_direction;

    // update velocity so that DynamicObject bouncess of the object it collided based on elasticity
    physics.velocity *= -physics.elasticity;
    physics.acceloration *= -physics.elasticity;
    inverse_direction.update(0.f, 0.f);
  }

  // updatePhysics implementation
  void DynamicObject::updatePhysics(float elapsed_time) {
    // apply gravity to the object
    float delta_x = physics.velocity.getX() * elapsed_time +
    0.5f * (physics.acceloration.getX() + PhysicsProperties::GravityX) * elapsed_time * elapsed_time;
    float delta_y = physics.velocity.getY() * elapsed_time +
    0.5f * (physics.acceloration.getY() + PhysicsProperties::GravityY) * elapsed_time * elapsed_time;
    physics.movePosition(Vector2f(delta_x, delta_y));
    // decrease acceloration and velocity based on physics.resistance_factor
    physics.applyResistance(elapsed_time);
    inverse_direction = Vector2f(-delta_x, -delta_y);
  }

  // setCollisionDirection implementation
  void DynamicObject::setCollisionDirection(Vector2f direction) {
    direction.normalize();
    collision_direction = direction;
  }

  // Get previous position
  Vector2f DynamicObject::getPrevPosition() {
    return physics.position + inverse_direction;
  }

}// end of namespace pe
