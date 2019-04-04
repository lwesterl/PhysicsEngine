/**
  *   @file Multichoice.hpp
  *   @author Lauri Westerholm
  *   @brief Multichoice for GameEngine demo, UI element
  */

#pragma once
#include "Switch.hpp" // contains font path macro
#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cstdint>


/**
  *   @namespace UI
  *   @brief namespace for UI elements used in PhysicsEngine demo
  */
namespace UI {

  /**
    *   @struct ValueLimits
    *   @brief Stores limits and describes those using sf::Texts
    */
  struct ValueLimits {
    int32_t max = 0;
    int32_t min = 0;
    sf::Text maxText;
    sf::Text minText;
  };

  /**
    *   @class Multichoice
    *   @brief Multichoice switch for demo
    *   @details This has a basic layout of two-part central frame that demostrates
    *   the current state (blue-white color theme). Aside the frame there is two
    *   Buttons: increase and decrease, mouse activated. Title is on top of the
    *   frame and it can be user defined.
    */
  class Multichoice: public sf::Drawable {

    public:
      static unsigned FontSize; /**< font size used */
      static float HorizontalDistance; /**< distance between main frame and buttons */
      static float VerticalDistance; /**< vertical distance between buttons */
      static float TitleDistance; /**< vertical distance between title and frames */
      static float FrameSpace; /**< how much smaller innnerFrame is on the both sides */
      static float TextDistance; /**< how much space is between innerFrame outside and valueText */

      /**
        *   @brief Empty constructor
        */
        Multichoice();

      /**
        *   @brief Deconstructor
        */
        virtual ~Multichoice() {}

      /**
        *   @brief Constructor
        *   @param x x coordinate position
        *   @param y y coordinate position
        *   @param width Multichoice frame width
        *   @param height Multichoice frame height
        *   @remark Positions are set based on title left corner
        */
        Multichoice(sf::String title, float x, float y, float width, float height, sf::Texture* upArrow, sf::Texture* downArrow);

      /**
        *   @brief Copy constructor
        *   @param multichoice to be copied
        */
        Multichoice(const Multichoice& multichoice);

      /**
        *   @brief Assignment operator
        *   @param multichoice to be assigned
        */
        Multichoice& operator=(const Multichoice& multichoice);

      /**
        *   @brief Set scale for Multichoice
        *   @param initial_value initial value
        *   @param max maximum value
        *   @param min minumum value
        *   @param interval how much one increase or decrease affects value
        */
        void setScale(int32_t initial_value, int32_t max, int32_t min, int32_t interval);

      /**
        *   @brief Set position
        *   @param x x coordinate, title left corner
        *   @param y y coordinate, title upper corner
        */
        void setPosition(float x, float y);

      /**
        *   @brief Draw Multichoice
        *   @details Switch inherits from sf::Drawable
        *   @param target Rendertarger where Switch is drawn to
        *   @param states sf::Renderstates
        */
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

      /**
        *   @brief Check if Multichoice has been toggled, ie. Buttons pressed
        *   @param x coordinate position
        *   @param y coordinate position
        *   @return true -> toggled
        */
        bool tryToggle(float x, float y);

      /**
        *   @brief Get value
        *   @return value
        */
        inline int32_t getValue() const {
          return value;
        }

      /**
        *   @brief Set enabled
        *   @param enable true -> drawn and buttons can be clicked
        */
        inline void setEnabled(bool enable) {
          enabled = enable;
        }

      /**
        *   @brief Increase value
        *   @details This should be passed as a function pointer to increaseButton
        *   and called by that Button
        */
        void increaseValue();

      /**
        *   @brief Decrease value
        *   @details This should be passed as a function pointer to decreaseButton
        *   and called by that Button
        */
        void decreaseValue();

    private:

      /**
        *   @brief Update valueText after value has been changed
        */
      void UpdateValueText();

      /**
        *   @brief Update innerFrame height when value (or scale) is changed
        */
      void UpdateInnerFrame();

      /**
        *   @brief Copy Multichoice
        *   @param multichoice to be copied
        */
      void Copy(const Multichoice& multichoice);

      bool enabled;
      int32_t value;
      int32_t interval;
      struct ValueLimits limits;
      sf::RectangleShape outerFrame;
      sf::RectangleShape innerFrame;
      sf::Text title;
      sf::Text valueText;
      sf::Font font;
      Button increaseButton;
      Button decreaseButton;

  };

}
