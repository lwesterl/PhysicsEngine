/**
  *   @file demo.cpp
  *   @author Lauri Westerholm
  *   @brief Demo/test for PhysicsEngine
  *   @details Contains the demo main and other source code
  */

#include "DemoUI.hpp"

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
