/**   @file Button.hpp
  *   @author Lauri Westerholm
  *   @brief Button class for PhysicsEngime demo
  */

#pragma once
#include "../../utils/Rect.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <functional>


/**   @namespace UI
  *   @brief namespace for UI elements used in PhysicsEngine demo
  */
namespace UI {

  /**
    *   @class Button
    *   @brief UI buttons used in demo
    *   @details This class needs texture element which should be stored elsewhere
    *   to save (reuse) resources
    */
  class Button: public sf::Drawable {
    public:

      /**
        *   @brief Basic constructor
        */
      Button();

      /**
        *   @brief Deconstructor
        */
      virtual ~Button() {}

      /**
        *   @brief Full constructor
        *   @param x x coordinate position, left corner
        *   @param y y coordinate position, upper corner
        *   @param texture refernce to texture from which image is created
        *   @param action executed on click, use std::bind
        */
      Button(float x, float y, sf::Texture* texture, std::function<void ()> const &action);

      /**
        *   @brief Copy constructor
        *   @param button to be copied
        */
      Button(const Button& button);

      /**
        *   @brief Assignment operator
        *   @param button to be assigned
        */
      Button& operator=(const Button& button);

      /**
        *   @brief Set Button position
        *   @param x x coordinate position, left corner
        *   @param y y coordinate position, upper corner
        */
      void setPosition(float x, float y);

      /**
        *   @brief Draw implementation from sf::Drawable
        *   @param target where Button is draw
        *   @param states sf::RenderStates used
        */
      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

      /**
        *   @brief Enable or disable Button
        *   @details When Button is disabled it isn't drawn and cannot be clicked
        *   @param enable true -> enable
        */
      inline void enable(bool enable) {
        enabled = enable;
      }

      /**
        *   @brief Check if the Button has been clicked
        *   @details If Button is clicked action is called, Button cannot be clicked
        *   if it's currently disabled
        *   @param x cursor x coordinate
        *   @param y cursor y coordinate
        */
      bool checkClicked(float x, float y);

    private:

      /**
        *   @brief Copy other Button
        *   @param button to be copied
        */
      void Copy(const Button& button);

      bool enabled;
      sf::Texture* texture; /**< stored itself somewhere else, must not go out of scope */
      sf::Sprite image;
      pe::Rectf frame; /**< could also use SFML RectangleShape */
      std::function<void ()> action;

  };

} // end of namespace UI
