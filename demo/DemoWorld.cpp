/**
  *   @file DemoWorld.cpp
  *   @author Lauri Westerholm
  *   @brief Source code for DemoWorld
  */

#include "DemoWorld.hpp"

/*  Class DemoWorld */

// set the gravity value
float pe::PhysicsProperties::GravityY = 100.f;
float pe::PhysicsProperties::GravityX = 0.f;

// static funtions, for setting gravity values
void DemoWorld::setGravityX(int gravity){
  pe::PhysicsProperties::GravityX = static_cast<float> (gravity);
}

void DemoWorld::setGravityY(int gravity) {
  pe::PhysicsProperties::GravityY = static_cast<float> (gravity);
}

// Constructor
DemoWorld::DemoWorld(sf::RenderWindow& window): window(window), shape(nullptr),
removeCollided(false), collisions(true) {}

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
    obj->getPhysicsObject()->setForce(pe::Vector2f(4.f, 500000.f));
  }
}

// Handle SFML window events
DemoObject* DemoWorld::handleEvent(sf::Event& event) {
  switch (event.type) {
    case sf::Event::MouseButtonPressed:
      return MousePress(event);
    default:
      return nullptr;
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
    // remove collided if removal true
    if (removeCollided) RemoveCollided(*it);
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

// Try to press DemoObject, private method
DemoObject* DemoWorld::MousePress(sf::Event& event) {
  if (event.mouseButton.button == sf::Mouse::Button::Left) {
    for (DemoObject* object : demoObjects) {
      if ((object->getPhysicsObject()->getObjectType() == pe::ObjectType::DynamicObject) &&
          (object->isInside(pe::Vector2f(event.mouseButton.x, event.mouseButton.y)))) {
        return object;
      }
    }
  }
  return nullptr;
}

// Remove collided objects, private method
void DemoWorld::RemoveCollided(struct pe::Collided& collided) {
  for (auto it = demoObjects.begin(); it != demoObjects.end(); ) {
    if (((*it)->getPhysicsObject() == collided[0]) || ((*it)->getPhysicsObject() == collided[1])) {
      delete *it;
      it = demoObjects.erase(it);
    }
    else it++;
  }
  // now remove PhysicsObjects, demoObject removal should left those untact
  if ((collided[0] != nullptr) && (!physWorld.removeObject(collided[0]))) {
    std::cout << "PhysicsObject removal error" << std::endl;
  }
  if ((collided[1] != nullptr) && (!physWorld.removeObject(collided[1]))) {
    std::cout << "PhysicsObject removal error" << std::endl;
  }
}

// Toggle object collisions on/off, that is done by adjusting PhysicsObjects collision_masks
void DemoWorld::toggleCollisions() {
  uint8_t mask;
  if (collisions) {
    collisions = false;
    mask = 0xFF; // no collisions
  }
  else {
    collisions = true;
    mask = 0x00; // all collisions
  }
  // update masks
  for (auto& object : demoObjects) {
    object->getPhysicsObject()->setCollisionMask(mask);
  }
}
