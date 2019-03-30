/**   @file Switch.cpp
  *   @author Lauri Westerholm
  *   @brief Source code for Switch
  */


#include "Switch.hpp"

namespace UI {

  /** Class Switch */

  // char size
  unsigned Switch::CharSize = 20;
  // spacing amount
  float Switch::SpacingVertical = 30.f;
  float Switch::SpacingHorizontal = 10.f;

  // constuctor
  Switch::Switch(): value(true), enabled(true) {}

  // full constructor
  Switch::Switch(float x, float y, sf::String title): value(true), enabled(true) {
    font.loadFromFile(FontPath);
    // if loading fails, no texts are visible
    this->title.setFont(font);
    statusText.setFont(font);
    this->title.setFillColor(sf::Color::Blue);
    statusText.setFillColor(sf::Color::White);
    this->title.setCharacterSize(Switch::CharSize);
    statusText.setCharacterSize(Switch::CharSize);
    this->title.setString(title);
    statusText.setString("ON");

    // set correct positions, try to center the title
    setPosition(x, y);
    // max three Courier chars
    outerFrame.setSize(sf::Vector2f(3 * Switch::CharSize/2.f + 2 * Switch::SpacingHorizontal, Switch::CharSize));
    outerFrame.setFillColor(sf::Color::Blue);
    // frameRect must exactly match outerFrame
    frameRect.setWidth(static_cast<float>(3 * Switch::CharSize/2.f + 2 * Switch::SpacingHorizontal));
    frameRect.setHeight(static_cast<float>(Switch::CharSize));
  }

  // set position
  void Switch::setPosition(float x, float y) {
    title.setPosition(x, y);
    outerFrame.setPosition(x - title.getString().getSize() * Switch::CharSize/2.f, y + Switch::SpacingHorizontal);
    frameRect.setPosition(pe::Vector2f(x - title.getString().getSize() * Switch::CharSize/2.f, y + Switch::SpacingHorizontal));
    statusText.setPosition(x - title.getString().getSize() * Switch::CharSize/2.f + Switch::SpacingHorizontal, y + Switch::SpacingHorizontal + Switch::CharSize/2.f);
  }

  // manually set value
  void Switch::setValue(bool value) {
    this->value = value;
    if (value) {
      statusText.setString("ON");
      outerFrame.setFillColor(sf::Color::Green);
    } else {
      statusText.setString("OFF");
      outerFrame.setFillColor(sf::Color::Red);
    }
  }

  // set title
  void Switch::setTitle(sf::String title) {
    this->title.setString(title);
    // Also update position
    setPosition(this->title.getPosition().x, this->title.getPosition().y);
  }

  // draw outerFrame, title and statusText
  void Switch::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (enabled) {
      target.draw(outerFrame, states);
      target.draw(title, states);
      target.draw(statusText, states);
    }
  }

  // try to toggle switch on / off
  bool Switch::tryToggle(float x, float y) {
    if (enabled && frameRect.contains(x, y)) {
      setValue(!value); // flip value
      return true;
    }
    return false;
  }


} // end of namespace UI
