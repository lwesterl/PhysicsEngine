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

  std::cout << "collision detection test" << std::endl;
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
  std::cout << "test successful" << std::endl;

  std::cout << std::endl << "canCollide and GetCollisionResult test" << std::endl;
  pe::DynamicObject dyn4(&shape, 1.f);
  dyn4.setPosition(pe::Vector2f(100.f, 100.f));
  pe::DynamicObject dyn5(&shape, 10.f);
  pe::StaticObject static1(&shape);
  static1.setPosition(pe::Vector2f(200.f, -500.f));
  pe::StaticObject static2(&shape);
  // by default all objects should collide
  assert(pe::CollisionDetection::canCollide(&dyn4, &dyn5));
  assert(pe::CollisionDetection::canCollide(&dyn4, &static1));
  assert(pe::CollisionDetection::canCollide(&static2, &static1));
  assert(pe::CollisionDetection::canCollide(&dyn5, &dyn5));
  dyn4.setCollisionMask(0xFF);
  assert(pe::CollisionDetection::canCollide(&dyn4, &dyn5) == false);
  assert(pe::CollisionDetection::canCollide(&static1, &dyn4) == false);
  dyn4.setCollisionMask(0x02);
  assert(pe::CollisionDetection::canCollide(&dyn4, &dyn5));
  assert(pe::CollisionDetection::canCollide(&static1, &dyn4));
  dyn5.setCollisionMask(0x02);
  assert(pe::CollisionDetection::canCollide(&dyn4, &dyn5));
  dyn4.setCollisionMask(0x00);
  dyn5.setCollisionMask(0x00);

  std::list<pe::PhysicsObject*> objects;
  // Notice: position must not affect GetCollisionResult
  objects = pe::CollisionDetection::GetCollisionResult(&dyn5, &dyn4);
  for (auto& item : objects) {
    std::cout << item << std::endl;
  }
  assert(objects.size() == 2);
  objects = pe::CollisionDetection::GetCollisionResult(&dyn4, &dyn4);
  assert(objects.size() == 2);
  objects = pe::CollisionDetection::GetCollisionResult(&static1, &dyn4);
  assert(objects.size() == 1);
  objects = pe::CollisionDetection::GetCollisionResult(&static1, &static2);
  assert(objects.size() == 0);

  static1.setCollisionMask(0x10);
  objects = pe::CollisionDetection::GetCollisionResult(&static1, &dyn4);
  assert(objects.size() == 1);
  dyn5.setCollisionMask(0xF0);
  objects = pe::CollisionDetection::GetCollisionResult(&dyn5, &dyn4);
  assert(objects.size() == 1);

  std::cout << "test successful" << std::endl;

  std::cout << std::endl << "All tests passed" << std::endl;
  return 0;
}
