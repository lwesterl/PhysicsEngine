/**
  *   @file PhysicsWorld.cpp
  *   @author Lauri Westerholm
  *   @brief Contains class PhysicsWorld
  */

#include "../include/PhysicsWorld.hpp"

namespace pe {

  /* Class PhysicsWorld */

  // Init class variables
  const int PhysicsWorld::GridCellSize = 5000;
  const unsigned PhysicsWorld::THREADS = std::thread::hardware_concurrency();
  int PhysicsWorld::WorldWidth = 100000;
  int PhysicsWorld::WorldHeight = PhysicsWorld::WorldWidth;
  float PhysicsWorld::IterarationsInterval = 1.f / 60.f;

  // Set how many iterations / s
  void PhysicsWorld::setIterationAmount(float iterations) {
    PhysicsWorld::IterarationsInterval = 1.f / iterations;
  }

  // Init Grid, private method
  void PhysicsWorld::InitGrid() {
    for (int j = - WorldHeight / 2; j <= WorldHeight / 2 - GridCellSize; j += GridCellSize) {
      for (int i = - WorldWidth / 2; i <= WorldWidth / 2 - GridCellSize; i += GridCellSize) {
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
    */
    collided.clear();
    /*
      1. Update object physics if DynamicObject (call updatePhysics with elapsed
       time, IterarationsInterval, as argument). This could be done in multiple
       threads at the same time, threads operate one grid cell. Activate object
       moved bool.
    */
    unsigned interval;
    if ((PhysicsWorld::THREADS > 0) && ((interval = grid->getCellsSize() / PhysicsWorld::THREADS) > 0)) {
      std::thread *workers = new std::thread[THREADS];
      auto it = grid->begin();
      auto it_inc = [](auto it, unsigned inc) { for (unsigned i = 0; i < inc; i++) it++; return it;};
      unsigned i = 0;
      for (; i < PhysicsWorld::THREADS - 1; i++) {
        auto it2 = it_inc(it, interval);
        workers[i] = std::thread(&PhysicsWorld::UpdateObjects, this, it, it2);
        it = it2;

      }
      workers[i] = std::thread(&PhysicsWorld::UpdateObjects, this, it, grid->cend());
      UpdateLooseObjects();
      // collect threads
      for (unsigned j = 0; j < PhysicsWorld::THREADS; j++) {
        workers[j].join();
      }
      delete[] workers;
    }
    else {
      UpdateObjects(grid->cbegin(), grid->cend());
      UpdateLooseObjects();
    }

    /*
      2. Move objects to the correct grid cells (call grid moveObjects)
    */
    //grid->moveObjects();

    /*
      3. Check collisions and store collided objects to collided
        - Collision may cause objects to change grid cells
        - But it's enough to update objects' grid cells during next update cycle
        step 2
    */

  }

  // Update PhysicsObjects in specific grid partion, private method
  void PhysicsWorld::UpdateObjects(std::map<Recti, Cell<PhysicsObject*>*>::const_iterator begin, std::map<Recti, Cell<PhysicsObject*>*>::const_iterator end) {
    for (auto it = begin; it != end; it++) {
      std::list<PhysicsObject*>& objects = it->second->entities;
      for (auto& object : objects) {
        if (object->getObjectType() == ObjectType::DynamicObject) {
          object->updatePhysics(PhysicsWorld::IterarationsInterval);
          object->setMoved(true);
        }
      }
    }
  }

  // Update loose_cell objects, private method
  void PhysicsWorld::UpdateLooseObjects() {
    std::list<PhysicsObject*> objects = grid->getLooseCell()->entities;
    for (auto& object : objects) {
      if (object->getObjectType() == ObjectType::DynamicObject) {
        object->updatePhysics(PhysicsWorld::IterarationsInterval);
        object->setMoved(true);
      }
    }
  }


  // Get collided PhysicsObjects as a list reference
  std::list<struct Collided>& PhysicsWorld::getCollided() {
    return collided;
  }

} // end of namespace pe
