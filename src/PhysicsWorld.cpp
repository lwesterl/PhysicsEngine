/**
  *   @file PhysicsWorld.cpp
  *   @author Lauri Westerholm
  *   @brief Contains class PhysicsWorld
  */

#include "../include/PhysicsWorld.hpp"

namespace pe {

  /* Class PhysicsWorld */

  // Init class variables
  const int PhysicsWorld::GridCellSize = 1000;
  float PhysicsWorld::IterarationsInterval = 1.f / 60.f;

  // Set how many iterations / s
  void PhysicsWorld::setIterationAmount(float iterations) {
    PhysicsWorld::IterarationsInterval = 1.f / iterations;
  }

  // Init Grid, private method
  void PhysicsWorld::InitGrid() {
    
  }

  // Constructor
  PhysicsWorld::PhysicsWorld(): grid(new PhysicsGrid()) {}

  // Deconstructor
  PhysicsWorld::~PhysicsWorld() {
    delete grid;
  }


} // end of namespace pe
