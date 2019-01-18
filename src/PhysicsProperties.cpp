/**
  *   @file PhysicsProperties.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source code for PhysicsProperties
  */


#include "../include/PhysicsProperties.hpp"

namespace pe {

  // Member variable initializations
  float PhysicsProperties::GravityX = 0.f;
  float PhysicsProperties::GravityY = 9.81f; // notice direction
  float PhysicsProperties::SizeScale = 0.1f;

  // Empty constructor
  PhysicsProperties::PhysicsProperties(): density(0.f), elasticity(0.f), inverse_mass(0.f) {}

  // Constructor
  PhysicsProperties::PhysicsProperties(float density, float area, bool static_object):
  density(std::abs(density)), elasticity(0.9f) {
    CalculateInverseMass(area, static_object);
  }

  // Set position
  void PhysicsProperties::setPosition(Vector2f pos) {
    position = pos + origin_transform;
  }

  // Calculate inverse of the object mass
  void PhysicsProperties::CalculateInverseMass(float area, bool static_object) {
    if (static_object) inverse_mass = 0.f;
    else {
      inverse_mass = 1.f / (area * density * PhysicsProperties::SizeScale);
    }
  }

}// end of namespace pe