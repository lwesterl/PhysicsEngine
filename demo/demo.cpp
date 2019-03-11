/**
  *   @file demo.cpp
  *   @author Lauri Westerholm
  *   @brief Demo/test for PhysicsEngine
  *   @details Contains the demo main and other source code
  */

#include "DemoWorld.hpp"

int main() {

  // create the main window
  sf::RenderWindow window(sf::VideoMode(800, 600), "PhysicsEngine Demo");

  // create DemoWorld
  DemoWorld demoWorld(window);
  demoWorld.initWorld();

  while(window.isOpen()) {
    sf::Event event;
    while(window.pollEvent(event)) {
      if (demoWorld.handleEvent(event) < 0) {
        // quit
        window.close();
        return 0;
      }
    }
    // clear all draw objects
    window.clear();
    // update demoWorld and draw it
    demoWorld.update();
    demoWorld.draw();
    // show updated window
    window.display();

  }

  return 0;
}
