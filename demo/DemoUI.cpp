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
  CreateUI();
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
    window.clear(sf::Color::White);
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
  window.setView(bottomToolbarView);
  window.draw(toolbarBackground);
  window.draw(buttons[0]);
  window.draw(buttons[1]);
  window.setView(window.getDefaultView());
  if (paused) {
    // draw also UI-elements for pause menu
    window.draw(pauseBackground);
    window.draw(switches[0]);
    window.draw(switches[1]);
  }
}

// Update UI related events, private method
bool DemoUI::HandleUIEvent(sf::Event& event) {
  switch (event.type) {
    case sf::Event::Closed:
      return false;
    case sf::Event::KeyPressed:
      return HandleKeyPress(event);
    case sf::Event::MouseButtonPressed:
      return HandleMousePress(event);
    default:
      return true;
  }
}

// Handle key presses, private method
bool DemoUI::HandleKeyPress(sf::Event& event) {
  if (event.key.code == sf::Keyboard::Escape) return false;
  if (event.key.code == sf::Keyboard::Space) pauseSwitch();
  return true;
}

// Handle mouse presses, private method
bool DemoUI::HandleMousePress(sf::Event& event) {
  if (event.mouseButton.button == sf::Mouse::Button::Left) {
    if (buttons[0].checkClicked(event.mouseButton.x, event.mouseButton.y - DemoUI::BottomToolStartHeight * DemoUI::WindowHeight)) return true;
    if (buttons[1].checkClicked(event.mouseButton.x, event.mouseButton.y - DemoUI::BottomToolStartHeight * DemoUI::WindowHeight)) return true;
    if (paused) {
      // check if pause menu UI-elements are pressed
      if (switches[0].tryToggle(event.mouseButton.x, event.mouseButton.y)) {
        demoWorld.toggleCollisions();
      }
      else if (switches[1].tryToggle(event.mouseButton.x, event.mouseButton.y)) {
        demoWorld.toggleObjectRemoval();
      }
    }
  }
  return true;
}

// Create UI for DemoUI, private method
void DemoUI::CreateUI() {
  // create view
  bottomToolbarView.setViewport(sf::FloatRect(0, DemoUI::BottomToolStartHeight, 1, 1.f - DemoUI::BottomToolStartHeight));
  bottomToolbarView.setSize(DemoUI::WindowWidth, (1.f - DemoUI::BottomToolStartHeight) * DemoUI::WindowHeight);
  bottomToolbarView.setCenter(sf::Vector2f(DemoUI::WindowWidth /2.f, (1.f - DemoUI::BottomToolStartHeight) * DemoUI::WindowHeight * 0.5f));
  // init UI-elements
  buttons[0] = UI::Button(10.f, 10.f, textureLoader.getTexture(UI::TextureName::StartStop), std::bind(&DemoUI::pauseSwitch, this));
  buttons[1] = UI::Button(100.f, 10.f, textureLoader.getTexture(UI::TextureName::Restart), std::bind(&DemoUI::pauseSwitch, this));
  toolbarBackground.setSize(bottomToolbarView.getSize());
  toolbarBackground.setFillColor(sf::Color(0, 0, 0, 220));
  pauseBackground.setSize(sf::Vector2f(DemoUI::WindowWidth, DemoUI::BottomToolStartHeight * DemoUI::WindowHeight));
  pauseBackground.setFillColor(sf::Color(0, 0, 0, 220));
  switches[0] = UI::Switch(0.35 * DemoUI::WindowWidth, DemoUI::BottomToolStartHeight * DemoUI::WindowHeight - 150.f, "Collisions");
  switches[1] = UI::Switch(0.7 * DemoUI::WindowWidth, DemoUI::BottomToolStartHeight * DemoUI::WindowHeight - 150.f, "Remove collided", false);
}
