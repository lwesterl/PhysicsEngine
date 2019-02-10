/**
  *   @file PhysicsGrid_test.cpp
  *   @author Lauri Westerholm
  *   @brief Contains test main for PhysicsGrid
  */


#include "../include/PhysicsGrid.hpp"
#include "../include/DynamicObject.hpp"
#include <iostream>
#include <cassert>


/**
  *   @brief Test main for PhysicsGrid
  *   @details Most of PhysicsGrid operations are executed through PhysicsWorld
  *   so PhysicsWorld_test contains more PhysicsGrid related tests. This is mostly
  *   a constructor test
  */

int main() {

  std::cout << "PhysicsGrid test" << std::endl << std::endl;
  std::cout << "Test PhysicsGrid and Cell constructors" << std::endl;
  pe::Cell<pe::PhysicsObject*> cell;
  pe::DynamicObject dyn;
  cell.entities.push_back(&dyn);

  pe::PhysicsGrid grid;
  assert(grid.addCell(pe::Recti(pe::Vector2i(100, 200), 1000, 1000)));
  pe::PhysicsGrid grid2 = grid;
  assert(!grid2.addCell(pe::Recti(pe::Vector2i(100, 200), 1000, 1000))); // shouldn't allow dulicate Cells

  std::cout << "All test passed" << std::endl;
  return 0;
}
