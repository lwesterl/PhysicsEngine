/**
  *   @file TextChoice.hpp
  *   @author Lauri Westerholm
  *   @brief Header for TextChoice class
  */

#pragma once
#include "../../utils/Rect.hpp"
#include "Switch.hpp" // contains the font macro
#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <deque>
#include <list>
#include <string>
#include <cstring>

#define UNUSED(a) do {(void)(a);} while(0) /**< Macro to hide unused variables */


/**   @namespace UI
  *   @brief namespace for UI elements used in PhysicsEngine demo
  */
namespace UI {


  /**
    *   @class TextChoice
    *   @brief UI element which contains texts that can be choiced
    *   @details TextChoice displays three texts: currently choosen, previous and
    *   following ones
    *   @remark Create TextChoices as pointers so that Button click won't cause seg faults
    */
  class TextChoice: public sf::Drawable {
    public:
      static unsigned TitleSize; /**< font size for TextChoice title */
      static unsigned FontSize; /**< font size used in TextChoice texts */
      static float HorizontalDistance; /**< distance between frame and buttons */
      static float VerticalDistance; /**< vertical distance between buttons */
      static float TitleDistance; /**< vertical distance between title and frame */
      static float FreeSpace; /**< free space between texts, see below */
      static float CenteringSpace; /**< space between frame and texts, see below */
      static float FontCompensation; /**< this is needed because font vertical size is approximated */

      /**   __________________________________
            |[CS] text 1                 [CS]|
            |            [FreeSpace]         |
            |[CS] text 2 is a bit longer [CS]|
            |            [FreeSpace]         |
            |[CS] text3                      |
            __________________________________

            CS = CenteringSpace
      **/

      /**
        *   @brief Empty constructor
        */
      TextChoice();

      /**
        *   @brief Deconstructor
        */
      virtual ~TextChoice();

      /**
        *   @brief Full constructor
        *   @param x position x coordinate
        *   @param y position y coordinate
        *   @param title TextChoice title
        *   @param text_list all text to be added to TextChoice
        *   @param start_index currently displayed text index
        *   @param upArrow Texture for increaseButton, use UI::TextureLoader
        *   @param downArrow Texture for decreaseButton, use UI::TextureLoader
        *   @remark x and y define the title position, TextChoice width and height
        *   are dynamically set based on FontSize and longest text
        */
      TextChoice(float x, float y, const char* title, std::list<const char*>& text_list, int start_index, sf::Texture* upArrow, sf::Texture* downArrow);

      /**
        *   @brief Copy constructor
        *   @param textChoice to be copied
        */
      TextChoice(const TextChoice& textChoice);

      /**
        *   @brief Assignment operator
        *   @param textChoice to be copied
        *   @return updated TextChoice
        */
      TextChoice& operator=(const TextChoice& textChoice);

      /**
        *   @brief Draw TextChoice
        *   @details Draw current text and previous & following texts
        *   @param target RenderTarget where object is draw to
        *   @param states current RenderStates
        */
      virtual void draw (sf::RenderTarget &target, sf::RenderStates states) const;

      /**
        *   @brief Set TextChoice enabled / disabled
        *   @param enable true -> TextChoice can be updated and drawn
        */
      inline void setEnabled(bool enable) {
        enabled = enable;
      }

      /**
        *   @brief Get currently chosen text
        *   @return std::string of current text
        */
      std::string getCurrentText() const;

      /**
        *   @brief Try to change currently displayed text
        *   @param x x position coordinate
        *   @param y y position coordinate
        *   @return true if currently shown value was changed
        */
      bool tryToggle(float x, float y);

      /**
        *   @brief Set position for TextChoice
        *   @param x position x coordinate
        *   @param y position y coordinate
        *   @remark This is the title position
        */
      void setPosition(float x, float y);

      /**
        *   @brief Try to show next text
        *   @remark this should be called by increaseButton
        */
      void showNextText();

      /**
        *   @brief Try to show previous text
        *   @remark this should be called by decreaseButton
        */
      void showPrevText();

    private:

      /**
        *   @brief Copy TextChoice content
        *   @param textChoice to be copied
        */
      void Copy(const TextChoice& textChoice);

      /**
        *   @brief Update text positions
        *   @details this should be called from constructor and showNextText & showPrevText.
        *   Positions the three drawn texts to correct positions
        */
      void UpdateTextPositions();

      bool enabled;
      int index;
      std::deque<sf::Text*> texts;
      Button increaseButton;
      Button decreaseButton;
      pe::Rectf increaseRect;
      pe::Rectf decreaseRect;
      sf::RectangleShape frame;
      sf::RectangleShape highlight;
      sf::Text title;
      sf::Font font;
  };

} // end of namespace UI
