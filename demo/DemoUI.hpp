/**
  *   @file DemoUI.hpp
  *   @author Lauri Westerholm
  *   @brief Contains DemoUI, UI for demo
  */

#pragma once
#include "DemoWorld.hpp"
#include <SFML/Graphics.hpp>

/**
  *   @class DemoUI
  *   @brief Defines UI for demo
  */
class DemoUI
{
  public:
    /**
      *   @brief Constructor for DemoUI
      *   @param window RenderWindow
      */
    DemoUI(sf::RenderWindow& window);

    /**
      *   @brief Deconstructor
      */
    virtual ~DemoUI() {}

    /**
      *   @brief Update window, UI and DemoWorld until window is closed
      *   @remark Call this from demo.cpp
      */
    void run();

    /**
      *   @brief Draw all UI objects
      */
    void drawUI();

    /**
      *   @brief Pause switch
      */
    void inline PauseSwitch() {
      paused ? paused = false: paused = true;
    }

  private:
    /**
      *   @brief Handle incoming UI related events
      *   @param event current sf::Event
      *   @return false if window should be closed, otherwise true
      */
    bool HandleUIEvent(sf::Event& event);

    /**
      *   @brief Handle incoming Key presses
      *   @param event sfml KeyPressEvent
      */
    bool HandleKeyPress(sf::Event& event);

    bool paused;
    sf::RenderWindow &window;
    DemoWorld demoWorld;

};
