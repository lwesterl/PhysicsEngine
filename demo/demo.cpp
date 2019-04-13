/**
  *   @file demo.cpp
  *   @author Lauri Westerholm
  *   @brief Demo/test for PhysicsEngine
  *   @details Contains the demo main
  *
  *   @mainpage Basic rigid body physics engine
  *   @section Instructions
  *   See Readmes provided for compile and usage instructions.
  *   @section Classes
  *   All classes can be found from Classes tab.
  *   There are two distinct types of classes: PhysicsEngine @ref pe classes and @ref UI classes which
  *   are used to create UI for demo. Then there is the demo itself and its classes.
  *   @section Limitations
  *   Currently physics work only for rect boxes. There is also no support for
  *   rotation nor realtime collision detection. Some glithes are know to exist.
  */

#include "DemoUI.hpp"

/**
  *   @brief Simple main for PhysicsEngine demo
  *   @details demo uses SFML to provide basic graphical user interface.
  *   Window is locked to certain size just to make things more simple
  *   (no external UI library used to create UI-elements)
  */
int main() {

  // create the main window
  sf::RenderWindow window(sf::VideoMode(DemoUI::WindowWidth, DemoUI::WindowHeight), "PhysicsEngine Demo",
                          sf::Style::Titlebar | sf::Style::Close);

  // create DemoUI
  DemoUI demoUI(window);
  // run DemoUI which handles practically everything
  demoUI.run();

  return 0;
}
