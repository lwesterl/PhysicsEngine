/**
  *   @file PhysicsGrid.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source for class PhysicsGrid
  */


#include "../include/PhysicsGrid.hpp"

namespace pe {

  // Empty constructor
  PhysicsGrid::PhysicsGrid() {}

  // Deconstructor
  PhysicsGrid::~PhysicsGrid() {
    Clear();
  }

  // Copy constructor
  PhysicsGrid::PhysicsGrid(const PhysicsGrid& grid) {
    Copy(grid);
  }

  // Assignment operator
  PhysicsGrid& PhysicsGrid::operator=(const PhysicsGrid& grid) {
    // delete old objects
    Clear();
    Copy(grid);
    return *this;
  }

  // Clear whole Grid, notice this is private method
  void PhysicsGrid::Clear() {
    // delete all Cells and memory allocated for them
    for (auto it = cells.begin(); it != cells.end();) {
      // delete all PhysicsObject pointers
      for (auto object = it->second->entities.begin(); object != it->second->entities.end();) {
        delete *object;
        object = it->second->entities.erase(object);
      }
      delete it->second;
      it = cells.erase(it);
    }
  }

  // Copy whole Grid, hard copy, private method
  void PhysicsGrid::Copy(const PhysicsGrid& grid) {
    for (auto it = grid.cells.begin(); it != grid.cells.end(); it++) {
      Cell<PhysicsObject*>* cell = new Cell<PhysicsObject*>;
      for (auto object = it->second->entities.begin(); object != it->second->entities.end(); object++) {
        if ((*object)->getObjectType() == ObjectType::DynamicObject) {
          DynamicObject* dyn = static_cast<DynamicObject*> (*object);
          cell->entities.push_back(new DynamicObject(*dyn));
        } else {
          StaticObject* stat = static_cast<StaticObject*> (*object);
          cell->entities.push_back(new StaticObject(*stat));
        }
      }
      cells.emplace(it->first, cell);
    }
  }

  // Add object to Cell in PhysicsGrid
  bool PhysicsGrid::addObject(PhysicsObject* object) {
    auto it = cells.find((Vector2i) object->getPosition());
    if (it != cells.end()) {
      it->second->entities.push_back(object);
      if (object->getObjectType() == ObjectType::DynamicObject) {
        it->second->active_cell = true;
      }
      return true;
    }
    return false;
  }

} // end of namespace pe
