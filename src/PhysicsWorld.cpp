/**
  *   @file PhysicsWorld.cpp
  *   @author Lauri Westerholm
  *   @brief Contains class PhysicsWorld
  */

#include "../include/PhysicsWorld.hpp"

namespace pe {

  /* Class PhysicsWorld */

  // Init class variables
  const int PhysicsWorld::GridCellSize = 2000;
  int PhysicsWorld::WorldWidth = 100000;
  int PhysicsWorld::WorldHeight = PhysicsWorld::WorldWidth;
  float PhysicsWorld::IterarationsInterval = 1.f / 60.f;

  // Set how many iterations / s
  void PhysicsWorld::setIterationAmount(float iterations) {
    PhysicsWorld::IterarationsInterval = 1.f / iterations;
  }

  // Init Grid, private method
  void PhysicsWorld::InitGrid() {
    for (int j = - WorldHeight / 2; j < WorldHeight / 2 - GridCellSize; j += GridCellSize) {
      for (int i = - WorldWidth / 2; i < WorldWidth / 2 - GridCellSize; i += GridCellSize) {
        // create empty Cells to grid
        grid->addCell(Recti(Vector2i(i, j), GridCellSize, GridCellSize));
      }
    }
  }

  // Constructor
  PhysicsWorld::PhysicsWorld(): grid(new PhysicsGrid()) {
    InitGrid();
  }

  // Deconstructor
  PhysicsWorld::~PhysicsWorld() {
    delete grid;
  }

  // Copy constructor
  PhysicsWorld::PhysicsWorld(const PhysicsWorld& world):
  grid(new PhysicsGrid(*world.grid)), collided(world.collided) {}

  // Assignment operator
  PhysicsWorld& PhysicsWorld::operator=(const PhysicsWorld& world) {
    collided.clear();
    grid = world.grid;
    collided = world.collided;
    return *this;
  }

  // Add PhysicsObject to PhysicsWorld, wrapper call for PhysicsGrid addObject
  bool PhysicsWorld::addObject(PhysicsObject* object) {
    return grid->addObject(object);
  }

  // Remove PhysicsObject from PhysicsWorld, wrapper call for PhysicsGrid removeObject
  bool PhysicsWorld::removeObject(PhysicsObject* object) {
    return grid->removeObject(object);
  }

  // Update PhysicsWorld PhysicsObject positions and calculate collision
  void PhysicsWorld::update() {
    /*
      STEPS
      0. init collided

      1. Update object physics if DynamicObject (call updatePhysics with elapsed
       time, IterarationsInterval, as argument). This could be done in multiple
       threads at the same time, threads operate one grid cell. Activate object
       moved bool.

      2. Move objects to the correct grid cells (call grid moveObjects)

      3. Check collisions and store collided objects to collided
        - Collision may cause objects to change grid cells
        - But it's enough to update objects' grid cells during next update cycle
        step 2
    */

  }

  // Get collided PhysicsObjects as a list reference
  std::list<struct Collided>& PhysicsWorld::getCollided() {
    return collided;
  }

} // end of namespace pe
