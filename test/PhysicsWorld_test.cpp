/**
  *   @file PhysicsWorld_test.cpp
  *   @author Lauri Westerholm
  *   @brief Contains test main for PhysicsWorld
  */


#include "../include/PhysicsWorld.hpp"
#include "../include/StaticObject.hpp"
#include "../include/DynamicObject.hpp"
#include <iostream>
#include <cassert>


/**
  *   @brief Test main for PhysicsWorld
  */
 int main() {
   std::cout << "PhysicsWorld Test" << std::endl << std::endl;
   std::cout << "Constructor test" << std::endl;
   pe::PhysicsWorld world;

   pe::Shape shape(100.f, 200.f);
   pe::StaticObject* static1 = new pe::StaticObject(&shape);
   assert(world.addObject(static1));
   pe::PhysicsWorld world2 = world;
   assert(world.removeObject(static1));
   pe::StaticObject* static2 = new pe::StaticObject(&shape);
   assert(world2.addObject(static2));
   assert(!world.removeObject(static2)); // not added to world
   assert(world2.removeObject(static2));

   pe::Shape shape2(344.f, 553.f);
   pe::DynamicObject* dyn1 = new pe::DynamicObject(&shape2, 1.f);
   // set position for dyn1
   dyn1->setPosition(pe::Vector2f(1000.f, 10000.f));
   assert(world.addObject(dyn1));
   pe::DynamicObject* dyn2 = new pe::DynamicObject(&shape2, 1.f);
   assert(world.addObject(dyn2));
   dyn2->setPosition(pe::Vector2f(1000.f, 10000.f));
   assert(world.removeObject(dyn1));
   assert(!world.removeObject(dyn2)); // world is not updated so position isn't updated so object cannot be removed at the moment
   dyn2->setPosition(pe::Vector2f(0.f, 0.f)); // object is returned to its original position which matches to PhysicsWorld position
   assert(world.removeObject(dyn2)); // now removal should succeed

   std::cout << "All PhysicsWorld tests passed" << std::endl;
   return 0;
 }
