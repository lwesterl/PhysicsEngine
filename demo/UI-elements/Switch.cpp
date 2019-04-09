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
  Switch::Switch(float x, float y, sf::String title, bool state): value(true), enabled(true) {
    font.loadFromFile(FontPath);
    // if loading fails, no texts are visible
    this->title.setFont(font);
    statusText.setFont(font);
    this->title.setFillColor(sf::Color::White);
    statusText.setFillColor(sf::Color::White);
    this->title.setCharacterSize(Switch::CharSize);
    statusText.setCharacterSize(Switch::CharSize);
    this->title.setString(title);
    if (state) {
      statusText.setString("ON");
      outerFrame.setFillColor(sf::Color::Green);
    }
    else {
      value = false;
      statusText.setString("OFF");
      outerFrame.setFillColor(sf::Color::Red);
    }

    // max three Courier chars
    outerFrame.setSize(sf::Vector2f(3 * Switch::CharSize/2.f + 2 * Switch::SpacingHorizontal, Switch::CharSize));
    // frameRect must exactly match outerFrame
    frameRect.setWidth(static_cast<float>(3 * Switch::CharSize/2.f + 2 * Switch::SpacingHorizontal));
    frameRect.setHeight(static_cast<float>(Switch::CharSize));

    // set correct positions, try to center the title
    setPosition(x, y);
  }

  // copy constructor
  Switch::Switch(const Switch& src_switch) {
    Copy(src_switch);
  }

  // assigment operator
  Switch& Switch::operator=(const Switch& src_switch) {
    Copy(src_switch);
    return *this;
  }

  // copy everthing, private method
  void Switch::Copy(const Switch& src_switch) {
    value = src_switch.value;
    enabled = src_switch.enabled;
    font = src_switch.font;
    title.setFont(font);
    title.setFillColor(src_switch.title.getFillColor());
    title.setCharacterSize(src_switch.title.getCharacterSize());
    title.setString(src_switch.title.getString());
    title.setPosition(src_switch.title.getPosition());
    statusText.setFont(font);
    statusText.setFillColor(src_switch.statusText.getFillColor());
    statusText.setCharacterSize(src_switch.statusText.getCharacterSize());
    statusText.setString(src_switch.statusText.getString());
    statusText.setPosition(src_switch.statusText.getPosition());
    frameRect = pe::Rectf(src_switch.frameRect);
    outerFrame.setSize(src_switch.outerFrame.getSize());
    outerFrame.setFillColor(src_switch.outerFrame.getFillColor());
    outerFrame.setPosition(src_switch.outerFrame.getPosition());
  }

  // set position
  void Switch::setPosition(float x, float y) {
    title.setPosition(x, y);
    outerFrame.setPosition(x, y + Switch::SpacingVertical);
    frameRect.setPosition(pe::Vector2f(x, y + Switch::SpacingVertical));
    statusText.setPosition(x + Switch::SpacingHorizontal, y + Switch::SpacingVertical - 0.1 * Switch::CharSize);
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
