/**
  *   @file DemoUI.hpp
  *   @author Lauri Westerholm
  *   @brief Contains DemoUI, UI for demo
  */

#pragma once
#include "DemoWorld.hpp"
#include "DemoLevelLoader.hpp"
#include "UI-elements/TextureLoader.hpp"
#include "UI-elements/Button.hpp"
#include "UI-elements/Multichoice.hpp"
#include "UI-elements/Switch.hpp"
#include "UI-elements/TextChoice.hpp"
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


#define ForceMultiplier 10000 /**< Used in MouseApplyForce to multiply mouse distance to get force */

  /**
    *   @struct MouseApplyForce
    *   @brief Contains DemoObject force apply related info
    */
  struct MouseApplyForce {
    bool leftHold = false; /**< left mouse currently pressed */
    sf::Vertex start; /**< line start here */
    sf::Vertex end; /**< line ends here */
    DemoObject* demoObject = nullptr; /**< pointer to the DemoObject which force should be applied to */

    /**
      *   @brief Constructor
      */
    MouseApplyForce() {
      start.color = sf::Color::Black;
      end.color = sf::Color::Black;
    }

    /**
      *   @brief Draw line
      *   @param window where drawn to
      */
    void draw(sf::RenderWindow& window) {
      sf::Vertex vertices[] = {start, end};
      window.draw(vertices, 2, sf::Lines);
    }

    /**
      *   @brief Set force for demoObject
      */
    void applyForce() {
      if (demoObject) {
        pe::Vector2f force((end.position.x - start.position.x) * ForceMultiplier,
                           (end.position.y - start.position.y) * ForceMultiplier);
        demoObject->getPhysicsObject()->setForce(force);
      }
    }

    /**
      *   @brief Update based on event
      *   @param object to which force is applied
      *   @param position new end position
      */
    void setEvent(DemoObject* object, sf::Vector2f position) {
      demoObject = object;
      leftHold = true;
      start.position = position;
    }
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

    /**
      *   @brif Restart current demo level
      */
    void restartSwitch();

  private:
    const static unsigned MultiChoiceAmount = 6; /**< amount of Multichoices */

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
      *   @brief Apply force to DemoObject based on mouseApplyForce
      *   @remark call only when not paused
      */
    void HandleForceApply();

    /**
      *   @brief Create all UI elements
      *   @details This should be called only from the constructor
      */
    void CreateUI();

    bool paused;
    sf::RenderWindow &window;
    DemoWorld demoWorld;
    UI::TextureLoader textureLoader;
    UI::Multichoice* multiChoices[DemoUI::MultiChoiceAmount]; // these need to be pointers, otherwise they cannot be trusthworhy called via Button actions
    UI::Button buttons[2];
    UI::Switch switches[2];
    UI::TextChoice* levelSelect; // same pointer requirement as multiChoices
    sf::RectangleShape toolbarBackground;
    sf::RectangleShape pauseBackground;
    sf::View bottomToolbarView;
    sf::Text buttonText[2];
    sf::Font font;
    struct MousePressDetails mousePressDetails;
    struct MouseApplyForce mouseApplyForce;
};
