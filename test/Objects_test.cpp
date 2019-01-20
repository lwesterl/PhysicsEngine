/**
  *   @file Objects_test.cpp
  *   @author Lauri Westerholm
  *   @brief Contains test main for DynamicOject and StaticObject
  */

#include "../utils/Vector2.hpp"
#include "../include/DynamicObject.hpp"
#include "../include/StaticObject.hpp"
#include "../include/Shape.hpp"
#include "../include/PhysicsProperties.hpp"
#include <iostream>
#include <cassert>
#include <list>

/**
  *   @brief Test man for DynamicOject and StaticObject
  */
int main() {

  std::cout << "Constructor test" << std::endl;
  std::list<pe::PhysicsObject*> objects;
  pe::Shape shape(100.f, 100.f);
  pe::StaticObject static1(&shape);
  pe::StaticObject static2 = pe::StaticObject(&shape);
  pe::StaticObject static3 = static2;
  assert(static1.getShape() == &shape);
  assert(static2.getShape() == static3.getShape() && static2.getShape() == static1.getShape());
  pe::DynamicObject dyn1 = pe::DynamicObject(&shape, 10.f);
  pe::StaticObject static4 = pe::StaticObject(&shape);
  assert(dyn1.getShape() == static4.getShape());
  // just push some objects to the list
  objects.push_back(&static1);
  objects.push_back(&static2);
  objects.push_back(&dyn1);
  std::cout << "test successful" << std::endl;

  std::cout << std::endl << "setOwner and getOwner test" << std::endl;
  std::cout << "owner: " << dyn1.getOwner() << " == nullptr" << std::endl;
  assert(dyn1.getOwner() == nullptr);
  std::cout << "owner type: " << dyn1.getOwnerType() << " == 0" << std::endl;
  dyn1.setOwner(static_cast<void *>(&static1));
  assert(static_cast<pe::StaticObject*>(dyn1.getOwner()) == &static1);
  dyn1.setOwner(nullptr, 100);
  assert(dyn1.getOwner() == nullptr && dyn1.getOwnerType() == 100);
  std::cout << "test successful" << std::endl;

  std::cout << std::endl << "getPhysics test" << std::endl;
  pe::PhysicsProperties &physics = dyn1.getPhysics();
  assert(physics.density == 10.f);
  std::cout << "inverse mass: " << physics.inverse_mass << std::endl;
  assert(1.f / physics.inverse_mass == shape.getArea() * physics.density * pe::PhysicsProperties::SizeScale);
  physics.density = 100.f;
  assert(dyn1.getPhysics().density == 100.f);
  std::cout << "test successful" << std::endl;

  std::cout << std::endl << "setPosition and getPosition test" << std::endl;
  pe::Shape shape2(20.f, 15.f);
  pe::StaticObject static5 = pe::StaticObject(&shape2);
  assert(static5.getPosition() == pe::Vector2f(0.f, 0.f));
  static5.setPosition(pe::Vector2f(-13.f, 90.f));
  assert(static5.getPosition() == pe::Vector2f(-13.f, 90.f));
  assert(static5.getPhysics().position == pe::Vector2f(-13.f, 90.f));
  std::cout << "test successful" << std::endl;

  std::cout << std::endl << "setOriginTransform and getOriginTransform test" << std::endl;
  pe::DynamicObject dyn2(&shape2, 1.f);
  dyn2.setOriginTransform(pe::Vector2f(-5.f, 100.f));
  assert(dyn2.getOriginTransform() == pe::Vector2f(-5.f, 100.f));
  assert(dyn2.getOriginTransform() == dyn2.getPhysics().origin_transform);
  std::cout << "test successful" << std::endl;

  std::cout << std::endl << "setElasticity and getElasticity test" << std::endl;
  std::cout << "elasticity: " << dyn2.getElasticity() << std::endl;
  assert(dyn2.getElasticity() == 0.9f); // default value 0.9
  dyn2.setElasticity(-3.0);
  assert(dyn2.getElasticity() == 3.f); // should take abs
  pe::StaticObject static6 = pe::StaticObject();
  assert(static6.getElasticity() == 0.f);
  std::cout << "test successful" << std::endl;

  std::cout << std::endl << "setForce and setVelocity tests" << std::endl;
  for (auto& item : objects) {
    item->setForce(pe::Vector2f(100.f, 0.f));
    item->setVelocity(pe::Vector2f(345.f, 50.f));
    if (item->getObjectType() == pe::ObjectType::DynamicObject) {
      assert(item->getPhysics().velocity == pe::Vector2f(345.f, 50.f));
    }
    else {
      assert(item->getPhysics().velocity == pe::Vector2f());
      assert(item->getPhysics().acceloration == pe::Vector2f());
    }
  }
  std::cout << "test successful" << std::endl;

  std::cout << "All tests passed" << std::endl;
  return 0;
}
