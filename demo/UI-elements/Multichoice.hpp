/**   @file Multichoice.hpp
  *   @author Lauri Westerholm
  *   @brief Multichoice for GameEngine demo, UI element
  */

#pragma once
#include <SFML/Graphics.hpp>

/**   @namespace UI
  *   @brief namespace for UI elements used in PhysicsEngine demo
  */
namespace UI {

  /**   @class Multichoice
    *   @brief Multichoice switch for demo
    */
  class Multichoice: sf::Drawable {

    public:

      /**   @brief Empty constructo
        *   @details creates a basic blue-green switch at position 0.f
        */
        Multichoice();

      /**   @brief Constructor
        *   @param x x coordinate position
        *   @param y y coordinate position
        *   @param intial_value starting value
        */
        Multichoice(float x, float y, int starting value);

    private:

      int value;
      sf::RectangleShape outerFrame;
      sf::RectangleShape innerFrame;

  };

}
