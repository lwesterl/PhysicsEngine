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
  // create rectShape
  rectShape = sf::RectangleShape(sf::Vector2f(shape->getHeight(), shape->getWidth()));
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

// Set color for rectShape
void DemoObject::setColor(sf::Color color) {
  rectShape.setFillColor(color);
}
