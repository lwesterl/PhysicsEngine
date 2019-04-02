/**   @file Multichoice.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source for Multichoice
  */


#include "Multichoice.hpp"

namespace UI {

  /* class Multichoice */

  // class member initialization
  unsigned Multichoice::FontSize = 20;
  float Multichoice::HorizontalDistance = 50.f;
  float Multichoice::VerticalDistance = 80.f;
  float Multichoice::TitleDistance = 30.f;
  float Multichoice::FrameSpace = 5.f;

  // empty constructor
  Multichoice::Multichoice(): value(0), interval(0) {}

  // constructor
  Multichoice::Multichoice(sf::String title, float x, float y, float width, float height, sf::Texture* upArrow, sf::Texture* downArrow):
  value(0), interval(0) {
    // if font loading fails, none of the text are visible
    font.loadFromFile(FontPath);

    this->title.setFont(font);
    this->title.setCharacterSize(Multichoice::FontSize);
    this->title.setString(title);
    limits.maxText.setFont(font);
    limits.maxText.setCharacterSize(Multichoice::FontSize);
    limits.minText.setFont(font);
    limits.minText.setCharacterSize(Multichoice::FontSize);
    valueText.setFont(font);
    valueText.setCharacterSize(Multichoice::FontSize);

    // set correct frame width and height
    outerFrame.setSize(sf::Vector2f(width, height));
    innerFrame.setSize(sf::Vector2f(width - 2 * Multichoice::FrameSpace, height));

    // set colors
    outerFrame.setFillColor(sf::Color::Blue);
    innerFrame.setFillColor(sf::Color::White);

    // set correct positions
    setPosition(x, y);

    // create Buttons
    increaseButton = Button(x + Multichoice::HorizontalDistance, y + Multichoice::VerticalDistance,
                            upArrow, std::bind(&Multichoice::increaseValue, this));
    decreaseButton = Button(x + Multichoice::HorizontalDistance, y + Multichoice::VerticalDistance,
                            downArrow, std::bind(&Multichoice::decreaseValue, this));
  }

  // set all scale related values
  void Multichoice::setScale(int32_t initial_value, int32_t max, int32_t min, int32_t interval) {
    value = initial_value;
    this->interval = interval;
    limits.max = max;
    limits.min = min;
    // convert to c-style string and then to sf::String (int32 fits in 11 chars)
    char str_max[12], str_min[12];
    snprintf(str_max, 12, "%d", limits.max);
    snprintf(str_min, 12, "%d", limits.min);
    limits.maxText.setString(str_max);
    limits.minText.setString(str_min);
    UpdateValueText();
  }

  // set all positions: title, frames, texts, buttons
  void Multichoice::setPosition(float x, float y) {
    title.setPosition(x, y);
    // font is monospace, Courier (following is an approximation)
    float title_width = static_cast<float>(Multichoice::FontSize)/2.f * title.getString().getSize();
    float adjust = (title_width - outerFrame.getSize().x) / 2.f;
    // set centered positions for the frames
    outerFrame.setPosition(x + adjust, y + Multichoice::TitleDistance);
    float difference = outerFrame.getSize().y - innerFrame.getSize().y;
    innerFrame.setPosition(x + adjust + Multichoice::FrameSpace, y + Multichoice::TitleDistance + difference);
  }

  // update valueText, private method
  void Multichoice::UpdateValueText() {
    char str_value[12];
    snprintf(str_value, 12, "%d", value);
    valueText.setString(str_value);
  }

  // update innerFrame height based on value, private method
  void Multichoice::UpdateInnerFrame() {
    if (value) {
      float value_multp = static_cast<float> (limits.max) - static_cast<float> (value);
      // set new height for innerFrame
      const sf::Vector2f& outer_size = outerFrame.getSize();
      innerFrame.setSize(sf::Vector2f(outer_size.x - 2 * Multichoice::FrameSpace, outer_size.y * value_multp));
      // update also position accordingly
      innerFrame.setPosition(innerFrame.getPosition().x, outerFrame.getPosition().y + (outerFrame.getSize().y + innerFrame.getSize().y));
    }
  }

  // draw frames, texts, buttons
  void Multichoice::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (enabled) {
      target.draw(outerFrame, states);
      target.draw(innerFrame, states);
      target.draw(title, states);
      target.draw(limits.minText);
      target.draw(limits.maxText);
      target.draw(valueText);
    }
  }

  // try toggle, check if Buttons pressed
  bool Multichoice::tryToggle(float x, float y) {
    if (increaseButton.checkClicked(x, y)) return true;
    if (decreaseButton.checkClicked(x, y)) return true;
    return false;
  }

  // increase value if possible
  void Multichoice::increaseValue() {
    if (value + interval < limits.max) value += interval;
    else value = limits.max;
  }

  // decrease value if possible
  void Multichoice::decreaseValue() {
    if (value - interval > limits.min) value -= interval;
    else value = limits.min;
  }


} // end of namespace UI
