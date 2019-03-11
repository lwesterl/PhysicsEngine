/**
  *   @file DemoObject.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source for DemoObject
  */

#include "DemoObject.hpp"

/* Class DemoObject */

// Empty constructor
DemoObject::DemoObject(): physicsObject(nullptr) {}

// Constructor
DemoObject::DemoObject(pe::ObjectType::ObjectType type, pe::Shape* shape, sf::Color color) {
  if (type == pe::ObjectType::ObjectType::StaticObject) {
    physicsObject = new pe::StaticObject(shape);
  } else {
    // use some density value
    physicsObject = new pe::DynamicObject(shape, 1.f);
  }
  // move physicsObject from left upper corner (like SFML rectShape)
  physicsObject->setOriginTransform(pe::Vector2f(-shape->getWidth()/2.f, -shape->getHeight()/2.f));
  // create rectShape
  rectShape = sf::RectangleShape(sf::Vector2f(shape->getWidth(), shape->getHeight()));
  rectShape.setFillColor(color);
}

// Copy another DemoObject, private method
void DemoObject::Copy(const DemoObject& demoObject) {
  if (demoObject.physicsObject->getObjectType() == pe::ObjectType::ObjectType::StaticObject) {
    pe::StaticObject* stat = static_cast<pe::StaticObject*> (demoObject.physicsObject);
    physicsObject = new pe::StaticObject(*stat);
  } else {
    pe::DynamicObject* dyn = static_cast<pe::DynamicObject*> (demoObject.physicsObject);
    physicsObject = new pe::DynamicObject(*dyn);
  }
  rectShape = demoObject.rectShape;
}

// Copy constructor
DemoObject::DemoObject(const DemoObject& demoObject) {
  Copy(demoObject);
}

// Assignment operator
DemoObject& DemoObject::operator=(const DemoObject& demoObject) {
  Copy(demoObject);
  return *this;
}

// Draw DemoObject
void DemoObject::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  // draw rectShape
  target.draw(rectShape, states);
}

// Set DemoObject position
void DemoObject::setPosition(float x, float y) {
  // both physicsObject and rectShape moved from left upper corner
  physicsObject->setPosition(pe::Vector2f(x, y));
  rectShape.setPosition(x, y);
}

// Update SFML position
void DemoObject::updatePosition() {
  // DynamicObject position already contains current origin_transform
  pe::Vector2f new_pos = physicsObject->getPosition();
  rectShape.setPosition(new_pos.getX(), new_pos.getY());
}

// Set color for rectShape
void DemoObject::setColor(sf::Color color) {
  rectShape.setFillColor(color);
}
