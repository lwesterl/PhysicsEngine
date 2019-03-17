/**
  *   @file DemoUI.cpp
  *   @author Lauri Westerholm
  *   @brief Source for DemoUI
  */


#include "DemoUI.hpp"

/* Class DemoUI */

// Constructor
DemoUI::DemoUI(sf::RenderWindow& window): paused(true), window(window), demoWorld(window) {
  demoWorld.initWorld();
}


// Run DemoUI until window is closed
void DemoUI::run() {
  while(window.isOpen()) {
    sf::Event event;
    while(window.pollEvent(event)) {
      if (! HandleUIEvent(event)) {
        // quit
        window.close();
        return;
      }
      if (! paused) {
        // Handle also DemoWorld events
        demoWorld.handleEvent(event);
      }
    }
    // clear all draw objects
    window.clear();
    // update demoWorld if not paused
    if (! paused) demoWorld.update();
    // draw all objects
    demoWorld.draw();
    drawUI();
    // show updated window
    window.display();
  }
}

// Draw all UI related objects
void DemoUI::drawUI() {
  return;
}

// Update UI related events, private method
bool DemoUI::HandleUIEvent(sf::Event& event) {
  switch (event.type) {
    case sf::Event::Closed:
      return false;
    case sf::Event::KeyPressed:
      return HandleKeyPress(event);
    default:
      return true;
  }
}

// Handle key presses, private method
bool DemoUI::HandleKeyPress(sf::Event& event) {
  if (event.key.code == sf::Keyboard::Escape) return false;
  if (event.key.code == sf::Keyboard::Space) PauseSwitch();
  return true;
}
