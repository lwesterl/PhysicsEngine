/**
  *   @file CollisionDetection_test.cpp
  *   @author Lauri Westerholm
  *   @brief Contains test main for CollisionDetection
  */

#include "../utils/Vector2.hpp"
#include "../include/CollisionDetection.hpp"
#include "../include/DynamicObject.hpp"
#include "../include/StaticObject.hpp"
#include "../include/Shape.hpp"
#include <iostream>
#include <cassert>

/**
  *   @brief Test main for CollisionDetection
  */

int main() {

  // create some Shape
  pe::Shape shape(100.f, 100.f);

  std::cout << "Rough collision detection test" << std::endl;
  pe::DynamicObject dyn1(&shape, 1.f);
  pe::DynamicObject dyn2(&shape, 1.f);
  dyn1.setPosition(pe::Vector2f(20.f, 20.f));
  dyn2.setPosition(pe::Vector2f(200.f, 200.f));
  assert(pe::CollisionDetection::calculateCollision(&dyn1, &dyn2) == false);
  dyn1.setPosition(pe::Vector2f(200.f, 200.f));
  assert(pe::CollisionDetection::calculateCollision(&dyn1, &dyn2));
  dyn2.setPosition(pe::Vector2f(250.f, 200.f));
  assert(pe::CollisionDetection::calculateCollision(&dyn1, &dyn2));
  dyn2.setPosition(pe::Vector2f(260.f, 290.f));
  assert(pe::CollisionDetection::calculateCollision(&dyn1, &dyn2));
  dyn2.setPosition(pe::Vector2f(300.f, 100.f));
  assert(pe::CollisionDetection::calculateCollision(&dyn1, &dyn2));
  dyn2.setPosition(pe::Vector2f(300.5f, 100.f));
  assert(pe::CollisionDetection::calculateCollision(&dyn1, &dyn2) == false);

  pe::Shape shape2(2.f, 3.f);
  pe::DynamicObject dyn3(&shape2, 1.f);
  dyn3.setPosition(pe::Vector2f(200.f, 200.f));
  assert(pe::CollisionDetection::calculateCollision(&dyn3, &dyn1));
  dyn3.setPosition(pe::Vector2f(255.f, 253.f));
  assert(pe::CollisionDetection::calculateCollision(&dyn3, &dyn1) == false);
  std::cout << "test succesful" << std::endl;

  std::cout << std::endl << "All tests passed" << std::endl;
  return 0;
}
