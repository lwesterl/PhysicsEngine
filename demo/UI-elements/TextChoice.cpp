/**
  *   @file TextChoice.cpp
  *   @author Lauri Westerholm
  *   @brief Source for TextChoice
  */

#include "TextChoice.hpp"

namespace UI {

  /* Class TextChoice */

  // class member initialization
  unsigned TextChoice::TitleSize = 20;
  unsigned TextChoice::FontSize = 12;
  float TextChoice::HorizontalDistance = 50.f;
  float TextChoice::VerticalDistance = 50.f;
  float TextChoice::TitleDistance = 30.f;
  float TextChoice::FreeSpace = 10.f;
  float TextChoice::CenteringSpace = 5.f;

  // constructor
  TextChoice::TextChoice(): enabled(false), index(0) {}

  // full constructor
  TextChoice::TextChoice(float x, float y, const char* title, std::list<const char*>& text_list,
                         int start_index, sf::Texture* upArrow, sf::Texture* downArrow):
                         enabled(true), index(start_index) {
    font.loadFromFile(FontPath);
    unsigned max_len = strlen(title);
    for (auto& text : text_list) {
      texts.push_back(sf::Text(text, font, TextChoice::FontSize));
      if (strlen(text) > max_len) max_len = strlen(text);
    }
    // create frame based on max_len
    frame = sf::RectangleShape(sf::Vector2f(max_len * TextChoice::FontSize / 2.f + 2.f * TextChoice::CenteringSpace,
                                            3.f * TextChoice::FontSize + 2.f * TextChoice::FreeSpace));
    frame.setFillColor(sf::Color::Blue);
    highlight = sf::RectangleShape(sf::Vector2f(max_len * TextChoice::FontSize / 2.f + 2.f * TextChoice::CenteringSpace,
                                                TextChoice::FontSize));
    highlight.setFillColor(sf::Color(0, 0, 255, 200));
    this->title = sf::Text(title, font, TextChoice::TitleSize);
    increaseButton = Button(x, y, upArrow, std::bind(&TextChoice::showNextText, this));
    decreaseButton = Button(x, y, downArrow, std::bind(&TextChoice::showPrevText, this));
    setPosition(x, y);
    UpdateTextPositions();
  }

  // copy everything, private method
  void TextChoice::Copy(const TextChoice& textChoice) {
    enabled = textChoice.enabled;
    index = textChoice.index;
    font = textChoice.font;
    for (auto& text : textChoice.texts) {
      sf::Text copy = sf::Text(text.getString(), font, text.getCharacterSize());
      copy.setPosition(text.getPosition());
      copy.setFillColor(text.getFillColor());
      texts.push_back(copy);
    }
    frame.setSize(textChoice.frame.getSize());
    frame.setFillColor(textChoice.frame.getFillColor());
    highlight.setSize(textChoice.frame.getSize());
    highlight.setFillColor(textChoice.frame.getFillColor());
    increaseButton = textChoice.increaseButton;
    decreaseButton = textChoice.decreaseButton;
    title.setFont(font);
    title.setString(textChoice.title.getString());
    title.setFillColor(textChoice.title.getFillColor());
    setPosition(textChoice.title.getPosition().x, textChoice.title.getPosition().y);
  }

  // copy constructor
  TextChoice::TextChoice(const TextChoice& textChoice) {
    Copy(textChoice);
  }

  // assignment operator
  TextChoice& TextChoice::operator=(const TextChoice& textChoice) {
    texts.clear();
    Copy(textChoice);
    return *this;
  }

  // draw TextChoice
  void TextChoice::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (enabled) {
      target.draw(title, states);
      target.draw(frame, states);
      target.draw(highlight, states);
      target.draw(increaseButton, states);
      target.draw(decreaseButton, states);
      for (int i = index - 1; i <= index + 1; i++) {
        try {
          target.draw(texts.at(i), states);
        } catch (std::out_of_range &e) {
          UNUSED(e); // no need to do anything
        }
      }
    }
  }

  // get current text
  std::string TextChoice::getCurrentText() const {
    try {
      return texts.at(index).getString().toAnsiString();
    } catch (std::out_of_range &e) {
      // just return an empty string, cannot really do anything else
      UNUSED(e);
      return "";
    }
  }

  // try to activate Buttons
  bool TextChoice::tryToggle(float x, float y) {
    if (increaseButton.checkClicked(x, y)) return true;
    if (decreaseButton.checkClicked(x, y)) return true;
    return false;
  }

  // update TextChoice position
  void TextChoice::setPosition(float x, float y) {
    title.setPosition(x, y);
    frame.setPosition(x, y + TextChoice::TitleDistance);
    increaseButton.setPosition(x + frame.getSize().x + TextChoice::HorizontalDistance, y + TextChoice::VerticalDistance);
    decreaseButton.setPosition(x + frame.getSize().x + TextChoice::HorizontalDistance, y + 2.f * TextChoice::VerticalDistance);
  }

  // try to show next text and update text positions accordingly
  void TextChoice::showNextText() {
    if (index + 1 < static_cast<int> (texts.size())) index++;
    UpdateTextPositions();
  }

  // try to show previous text and update text positions via UpdateTextPositions
  void TextChoice::showPrevText() {
    if (index - 1 > 0) index--;
    UpdateTextPositions();
  }


  // update text positions, private method
  void TextChoice::UpdateTextPositions() {
    sf::Vector2f pos = frame.getPosition();
    int j = 0;
    for (int i = index - 1; i < index + 2; i++) {
      try {
        texts.at(i).setPosition(pos.x + TextChoice::FreeSpace, pos.y + j * (TextChoice::FreeSpace + TextChoice::FontSize));
      } catch (std::out_of_range &e) {
        // that text doesn't exist so just don't update it
        UNUSED(e);
      }
      j++;
    }
  }


} // end of namespace UI
