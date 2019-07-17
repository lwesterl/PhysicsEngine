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
  grid.addCells(1000, 1000, 10);
  pe::PhysicsGrid grid2 = grid;
  int x, y;
  y = 0;
  for (auto it = grid2.cbegin(); it != grid2.cend(); it++) {
    y++;
    x = 0;
    for (auto it2 = it->cbegin(); it2 != it->cend(); it2++) {
      x++;
    }
    assert(x == 100); // 100 == grid width / grid cell size
  }
  assert(y == 100); // 100 = grid height / grid cell size

  std::cout << "All test passed" << std::endl;
  return 0;
}
