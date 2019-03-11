/**
  *   @file DemoWorld.cpp
  *   @author Lauri Westerholm
  *   @brief Source code for DemoWorld
  */

#include "DemoWorld.hpp"

/*  Class DemoWorld */

// set the gravity value
float pe::PhysicsProperties::GravityY = 100.f;

// Constructor
DemoWorld::DemoWorld(sf::RenderWindow& window): window(window), shape(nullptr) {}

// Deconstructor
DemoWorld::~DemoWorld() {
  if (shape) {
    delete shape;
  }
  for (auto it = demoObjects.begin(); it != demoObjects.end();) {
    delete *it;
    it = demoObjects.erase(it);
  }
}

// Init DemoWorld
void DemoWorld::initWorld() {
  shape = new pe::Shape(40.f, 20.f);
  // create couple DemoObjects
  for (int i = 0; i < 10; i++) {
    DemoObject* obj = new DemoObject(pe::ObjectType::StaticObject, shape, sf::Color::Red);
    obj->setPosition(static_cast<float>(i * 50), static_cast<float>(i * 100));
    // add object to physWorld
    physWorld.addObject(obj->getPhysicsObject());
    demoObjects.push_back(obj);
  }
  for (int i=0; i < 10; i++) {
    DemoObject* obj = new DemoObject(pe::ObjectType::DynamicObject, shape, sf::Color::Green);
    obj->setPosition(static_cast<float>(i * 100), static_cast<float>(i * 50));
    // add object to physWorld
    physWorld.addObject(obj->getPhysicsObject());
    demoObjects.push_back(obj);
  }
}

// Handle SFML window events
int DemoWorld::handleEvent(sf::Event& event) {
  switch (event.type) {
    case sf::Event::Closed:
      return -1;
    case sf::Event::MouseMoved:
      return MouseMove(event);
    case sf::Event::MouseButtonPressed:
      return MousePress(event);
    default:
      return 0;
  }

}

// Update DemoWorld periodically
void DemoWorld::update() {
  // update PhysicsWorld
  physWorld.update();
  for (auto& object : demoObjects) {
    object->updatePosition();
  }
  int num = 0;
  std::list<struct pe::Collided>& collided = physWorld.getCollided();
  for (auto it = collided.begin(); it != collided.end(); it++) {
    num++;
  }
  std::cout << "Collisions: " << num << std::endl;
}

// Draw DemoWorld
void DemoWorld::draw() {
  // Draw all DemoObjects
  for (auto& object : demoObjects) {
    window.draw(*object);
  }
}

// Try to move DemoObject, private method
int DemoWorld::MouseMove(sf::Event& event) {
  return 0;
}

// Try to activate DemoObject, private method
int DemoWorld::MousePress(sf::Event& event) {
  return 0;
}
