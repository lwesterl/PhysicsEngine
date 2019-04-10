/**
  *   @file DynamicObject.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source code for DynamicObject
  */


#include "../include/DynamicObject.hpp"

namespace pe {

  // Empty constructor
  DynamicObject::DynamicObject(): PhysicsObject(),
  alreadyCollided(false), updatesFromPrevCollision(0) {}

  // Constructor
  DynamicObject::DynamicObject(Shape *shape, float density):
  PhysicsObject(shape, density, false, ObjectType::DynamicObject),
  alreadyCollided(false), updatesFromPrevCollision(0) {}

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
  void DynamicObject::collisionAction(Vector2f position_change, bool dynamic_dynamic_collision) {
    // move DynamicObject to inverse direction to counter collision
    Vector2f direction_unit_vector = Vector2f(ABS(inverse_direction.getX()), ABS(inverse_direction.getY()));
    direction_unit_vector.normalize();
    // update velocity and acceloration so that DynamicObject bouncess of the object it collided based on elasticity
    physics.velocity = physics.velocity * physics.elasticity * collision_direction ;
    physics.acceloration = physics.acceloration * physics.elasticity * collision_direction;

    if (! alreadyCollided) {
      physics.position += direction_unit_vector * position_change * collision_direction;
      alreadyCollided = true;
      if (! dynamic_dynamic_collision) updatesFromPrevCollision = 0; // these values indicate that object position may be non-valid and return to prevPosition is needed
    } else {
      // just return DynamicObject to prev position to avoid glithing
      physics.setPosition(getPrevPosition());
      updatesFromPrevCollision++; // this need to be adjusted to indicate that prevPosition can be again updated
    }
  }

  // updatePhysics implementation
  void DynamicObject::updatePhysics(float elapsed_time) {
    // apply gravity to the object
    if (updatesFromPrevCollision < std::numeric_limits<unsigned>::max()) updatesFromPrevCollision++;
    float delta_x = physics.velocity.getX() * elapsed_time +
    0.5f * (physics.acceloration.getX() + PhysicsProperties::GravityX) * elapsed_time * elapsed_time;
    float delta_y = physics.velocity.getY() * elapsed_time +
    0.5f * (physics.acceloration.getY() + PhysicsProperties::GravityY) * elapsed_time * elapsed_time;
    if (updatesFromPrevCollision > 1) prevPosition = physics.position;
    physics.movePosition(Vector2f(delta_x, delta_y));
    // decrease acceloration and velocity based on physics.resistance_factor
    physics.applyResistance(elapsed_time);
    inverse_direction = Vector2f(-delta_x, -delta_y);
    alreadyCollided = false;
  }

  // setCollisionDirection implementation
  void DynamicObject::setCollisionDirection(Vector2f direction) {
    direction.normalize();
    collision_direction = direction;
  }

  // Get previous position
  Vector2f DynamicObject::getPrevPosition() {
    return prevPosition - physics.origin_transform;
  }

}// end of namespace pe
