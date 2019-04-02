/**
  *   @file Button.cpp
  *   @author Lauri Westerholm
  *   @brief Source code for Button class used PhysicsEngine demo
  */

#include "Button.hpp"

namespace UI {


  /** Class Button */

  // constructor
  Button::Button(): enabled(true), texture(nullptr) {}

  // full constructor
  Button::Button(float x, float y, sf::Texture* texture, std::function<void ()> const &action):
  enabled(true), texture(texture), action(action) {
    image = sf::Sprite(*texture);
    // create frame based on texture size
    sf::Vector2u size = texture->getSize();
    frame.setWidth(static_cast<float> (size.x));
    frame.setHeight(static_cast<float> (size.y));
    setPosition(x, y);
  }

  // copy other Button, private method
  void Button::Copy(const Button& button) {
    enabled = button.enabled;
    texture = button.texture;
    image = sf::Sprite(*texture);
    frame = button.frame;
    action = button.action;
    setPosition(button.image.getPosition().x, button.image.getPosition().y);
  }

  // copy construtor
  Button::Button(const Button& button) {
    Copy(button);
  }

  // Assignment operator
  Button& Button::operator=(const Button& button) {
    Copy(button);
    return *this;
  }

  // set new position
  void Button::setPosition(float x, float y) {
    frame.setPosition(pe::Vector2f(x, y));
    image.setPosition(sf::Vector2f(x, y));
  }

  // draw Button: image (sf::Sprite)
  void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    if (enabled) target.draw(image, states);
  }

  // check if Button has been clicked
  bool Button::checkClicked(float x, float y) {
    if (enabled && frame.contains(x, y)) {
      action();
      return true;
    }
    return false;
  }


} // end of namespace Button
