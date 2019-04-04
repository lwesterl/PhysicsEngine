/**
  *   @file DemoUI.hpp
  *   @author Lauri Westerholm
  *   @brief Contains DemoUI, UI for demo
  */

#pragma once
#include "DemoWorld.hpp"
#include "UI-elements/TextureLoader.hpp"
#include "UI-elements/Button.hpp"
#include "UI-elements/Multichoice.hpp"
#include "UI-elements/Switch.hpp"
#include <SFML/Graphics.hpp>
#include <chrono>


/**
  *   @struct MousePressDetails
  *   @brief Used to store information about mouse presses
  *   @details This is needed for Multichoices to increment the value on mouse hold
  */
  struct MousePressDetails {
    bool leftHold = false; /** tells whether left mouse button is being hold down */
    std::chrono::steady_clock::time_point prevTime; /** time when the mouse press was previous time registered */
    UI::Multichoice* multiChoice = nullptr; /** Multichoice which was pressed when hold started */
  };

/**
  *   @class DemoUI
  *   @brief Defines UI for demo
  *   @details Non-copyable
  */
class DemoUI
{
  public:
    const static unsigned WindowWidth = 800; /**< window width */
    const static unsigned WindowHeight = 600; /**< window height */
    constexpr static float BottomToolStartHeight = 0.875; /**< tells where bottom toolbar starts, must in range of 0 - 1 */
    const static int PressDuration = 200; /**< after this duration of millis has elapsed mouse hold triggers a new press */

    /**
      *   @brief Constructor for DemoUI
      *   @param window RenderWindow
      */
    DemoUI(sf::RenderWindow& window);

    /**
      *   @brief Deconstructor
      */
    virtual ~DemoUI();

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
    void inline pauseSwitch() {
      paused ? paused = false: paused = true;
    }

  private:

    NON_COPYABLE(DemoUI); /** make non-copyable, defined in TextureLoader.hpp */

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

    /**
      *   @brief Handle mouse presses
      *   @param event sfml MousePressEvent
      */
    bool HandleMousePress(sf::Event& event);

    /**
      *   @brief Handle continous mouse hold for Multichoices
      *   @details should be called when pause menu is active to update mousePressDetails
      *   Access directly to mouse state via sf::Mouse
      */
    void HandleMouseHold();

    /**
      *   @brief Create all UI elements
      *   @details This should be called only from the constructor
      */
    void CreateUI();

    bool paused;
    sf::RenderWindow &window;
    DemoWorld demoWorld;
    UI::TextureLoader textureLoader;
    UI::Multichoice* multiChoices[4]; // these need to be pointers, otherwise they cannot be trusthworhy called via Button actions
    UI::Button buttons[2];
    UI::Switch switches[2];
    sf::RectangleShape toolbarBackground;
    sf::RectangleShape pauseBackground;
    sf::View bottomToolbarView;
    struct MousePressDetails mousePressDetails;
};
