/**
  *   @file DemoWorld.cpp
  *   @author Lauri Westerholm
  *   @brief Source code for DemoWorld
  */

#include "DemoWorld.hpp"

/*  Class DemoWorld */

// Constructor
DemoWorld::DemoWorld(sf::RenderWindow& window): window(window), shape(nullptr) {}

// Deconstructor
DemoWorld::~DemoWorld() {
  if (shape != nullptr) {
    delete shape;
  }
}

// Init DemoWorld
void DemoWorld::initWorld() {

}

// Handle SFML window events
int DemoWorld::handleEvent(sf::Event& event) {
  return -1;
}

// Update DemoWorld periodically
void DemoWorld::update() {

}

// Draw DemoWorld
void DemoWorld::draw() {

}
