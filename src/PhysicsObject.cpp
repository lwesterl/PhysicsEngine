/**
  *   @file PhysicsObject.cpp
  *   @author Lauri Westerholm
  *   @brief Source for PhysicsObject
  */

#include "../include/PhysicsObject.hpp"

namespace pe {

  // Constructor
  PhysicsObject::PhysicsObject(Shape *shape, float density, bool static_object, ObjectType::ObjectType type):
  shape(shape), physics(PhysicsProperties(density, shape->getArea(), static_object)), collision_mask(0x00), type(type), moved(false) {}

  // Get ObjectType
  ObjectType::ObjectType PhysicsObject::getObjectType() const {
    return type;
  }

  // Set owner object
  void PhysicsObject::setOwner(void* owner, int type) {
    this->owner = std::make_pair(owner, type);
  }

  // Get owner
  void* PhysicsObject::getOwner() {
    return owner.first;
  }

  // Get owner type
  int PhysicsObject::getOwnerType() const {
    return owner.second;
  }

  // Get shape
  Shape* PhysicsObject::getShape() {
    return shape;
  }

  // Get physics
  PhysicsProperties& PhysicsObject::getPhysics() {
    return physics;
  }

  // Set PhysicsObject position in PhysicsWorld
  void PhysicsObject::setPosition(Vector2f position) {
    physics.setPosition(position);
    moved = true;
  }

  // Get PhysicsObject position in PhysicsWorld
  Vector2f& PhysicsObject::getPosition() {
    return physics.position;
  }

  // Get min position in PhysicsWorld
  Vector2f PhysicsObject::getMinPosition() {
    return getPosition() + shape->getMin();
  }

  // Get max position in PhysicsWorld
  Vector2f PhysicsObject::getMaxPosition() {
    return getPosition() + shape->getMax();
  }

  // Set origin transform for PhysicsObject
  void PhysicsObject::setOriginTransform(Vector2f transform) {
    physics.origin_transform = transform;
  }

  // Get origin transform of PhysicsObject
  Vector2f& PhysicsObject::getOriginTransform() {
    return physics.origin_transform;
  }

  // Set elasticity of PhysicsObject
  void PhysicsObject::setElasticity(float elasticity) {
    physics.elasticity = std::abs(elasticity);
  }

  // Get elasticity of PhysicsObject
  float PhysicsObject::getElasticity() {
    return physics.elasticity;
  }

  // Set collision_mask
  void PhysicsObject::setCollisionMask(uint8_t mask) {
    collision_mask = mask;
  }

  // Get collision_mask
  uint8_t PhysicsObject::getCollisionMask() {
    return collision_mask;
  }


}// end of namespace pe
