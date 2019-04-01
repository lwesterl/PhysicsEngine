/**
  *   @file TextureLoader.cpp
  *   @author Lauri Westerholm
  *   @brief Source for TextureLoader class
  */

#include "TextureLoader.hpp"

namespace UI {

  /* Class TextureLoader */

  // Init TexturePaths
  std::map<TextureName::TextureName, const std::string> TextureLoader::TexturePaths =
  {
    { TextureName::UpArrow, "img/up_arrow.png" },
    { TextureName::DownArrow, "img/down_arrow.png" },
    { TextureName::StartStop, "img/pause_play.png" },
    { TextureName::Restart, "img/restart.png" }
  };

  // Constructor
  TextureLoader::TextureLoader() {
    // a little sketchy
    for (int i = TextureName::UpArrow; i != TextureName::Restart; i++) {
      sf::Texture* texture = new sf::Texture();
      texture->loadFromFile(TextureLoader::TexturePaths[static_cast<TextureName::TextureName> (i)]);
      textures.emplace(std::make_pair(static_cast<TextureName::TextureName> (i), texture));
    }
  }

  // Deconstructor
  TextureLoader::~TextureLoader() {
    for (auto it = textures.begin(); it != textures.end(); ) {
      // free memory used by sf::Textures
      delete(it->second);
      it = textures.erase(it);
    }
  }

  // Get pointer to texture
  sf::Texture* TextureLoader::getTexture(TextureName::TextureName texture) {
    return textures[texture];
  }


} // end of namespace UI
