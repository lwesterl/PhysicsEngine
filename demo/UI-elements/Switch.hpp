/**
  *   @file Switch.hpp
  *   @author Lauri Westerholm
  *   @brief Header for UI switch used in PhysicsEngine demo
  */


#pragma once
#include "../../utils/Rect.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>


#define FontPath "UI-elements/fonts/Courier.ttf" /**< font file path, monospace font */

/**
  *   @namespace UI
  *   @brief namespace for UI elements used in PhysicsEngine demo
  */
namespace UI {


  /**
    *   @class Switch
    *   @brief ON-OFF -style switch for demo
    */

  class Switch: public sf::Drawable {
    public:

      static unsigned CharSize;  /**< char size used in text */
      static float SpacingVertical; /**< amount of vertical space between title and outerFrame */
      static float SpacingHorizontal; /**< amount of horizontal space between innerText and outerFrame */

      /**
        *   @brief Constructor
        */
      Switch();

      /**
        *   @brief Deconstructor
        */
      virtual ~Switch() {}


      /**
        *   @brief Constuctor which takes positional arguments
        *   @param x x coordinate position
        *   @param y y coordinate position
        *   @param state tells whether Switch is on or off by default
        *   @remark x and y is the position for left corner of the title
        */
      Switch(float x, float y, sf::String title, bool state=true);

      /**
        *   @brief Copy constructor
        *   @param switch to be copied
        */
      Switch(const Switch& src_switch);

      /**
        *   @brief Assignment operator
        *   @param switch to be assigned
        */
      Switch& operator=(const Switch& src_switch);

      /**
        *   @brief Get value
        *   @return value
        */
      inline bool getValue() const {
        return value;
      }

      /**
        *   @brief Set position for the switch
        *   @param x x coordinate position
        *   @param y y coordinate position
        *   @remark position is the position for left corner of the title
        */
      void setPosition(float x, float y);

      /**
        *   @brief change value manually
        *   @param value new value, true or false
        */
      void setValue(bool value);

      /**
        *   @brief Set title
        *   @param title new title text
        */
      void setTitle(sf::String title);

      /**
        *   @brief Draw Switch
        *   @details Switch inherits from sf::Drawable
        *   @param target Rendertarger where Switch is drawn to
        *   @param states sf::Renderstates
        */
      virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

      /**
        *   @brief Set enabled
        *   @param enable true -> Switch drawn and can be activated
        */
      inline void enable(bool enable) {
        enabled = enable;
      }

      /**
        *   @brief Try to toggle the switch
        *   @details switch is toggled if x and y are inside outerFrame
        *   @param x x coordinate position
        *   @param y y coordinate position
        */
      bool tryToggle(float x, float y);

    private:

      /**
        *   @brief Copy everything from other Switch
        *   @param switch to be copied
        */
      void Copy(const Switch& src_switch);

      bool value;
      bool enabled;
      sf::RectangleShape outerFrame;
      sf::Text statusText;
      sf::Text title;
      sf::Font font;
      pe::Rectf frameRect; /**< Could also use SFML sf::Rect implementation */

  };

} // end of namespace UI
