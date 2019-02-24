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
  PhysicsProperties::PhysicsProperties(): angle(0.f), density(0.f), elasticity(0.f),
  inverse_mass(0.f), resistance_factor(2.f) {}

  // Constructor
  PhysicsProperties::PhysicsProperties(float density, float area, bool static_object):
  angle(0.f), density(std::abs(density)), elasticity(0.9f) {
    CalculateInverseMass(area, static_object);
  }

  // Set position
  void PhysicsProperties::setPosition(Vector2f pos) {
    position = pos + origin_transform;
  }

  // Move position
  void PhysicsProperties::movePosition(Vector2f move) {
    position = position + origin_transform + move;
  }

  // Apply resisting forces
  void PhysicsProperties::applyResistance(float elapsed_time) {
    velocity.update(velocity.getX() * (1.f - elapsed_time / resistance_factor),
                    velocity.getY() * (1.f - elapsed_time / resistance_factor));
    acceloration.update(acceloration.getX() * (1.f - elapsed_time / sqrt(resistance_factor)),
                    acceloration.getY() * (1.f - elapsed_time / sqrt(resistance_factor)));
  }

  // Calculate inverse of the object mass
  void PhysicsProperties::CalculateInverseMass(float area, bool static_object) {
    if (static_object) inverse_mass = 0.f;
    else {
      inverse_mass = 1.f / (area * density * PhysicsProperties::SizeScale);
    }
  }

}// end of namespace pe
