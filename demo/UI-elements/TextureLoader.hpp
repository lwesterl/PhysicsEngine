/**
  *   @file TextureLoader.hpp
  *   @author Lauri Westerholm
  *   @brief Header for TextureLoader class
  */

#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>

/**< Macro which makes class non-copyable */
#define NON_COPYABLE(Typename) \
  Typename(const Typename&) = delete; \
  Typename& operator=(const Typename&) = delete

/**   @namespace UI
  *   @brief namespace for UI elements used in PhysicsEngine demo
  */
namespace UI {

  /**
    *   @namespace TextureName
    *   @brief Used to avoid namespace collisions, contains TextureName enum
    */
  namespace TextureName {
    /**
      *   @enum TextureName
      *   @brief enum for Texture tags
      */
    enum TextureName {
      UpArrow,
      DownArrow,
      StartStop,
      Restart
    };
  } // end of namespace TextureName


  /**
    *   @class TextureLoader
    *   @brief Loads and stores textures used in Buttons
    *   @details Non-copyable
    */

  class TextureLoader {
    public:
      static std::map<TextureName::TextureName, const std::string> TexturePaths; /**< map between texture names and texture paths */

      /**
        *   @brief Constructor
        *   @details Creates and stores all textures
        */
      TextureLoader();

      /**
        *   @brief Deconstructor
        *   @details Deletes all memory allocated for Texture -> all those pointer
        *   will invalidate, so this TextureLoader must not go out of scope
        *   before Buttons using the textures
        */
      virtual ~TextureLoader();

      /**
        *   @brief Get correct texture
        *   @param texture Texturename enum value mathcing the texture
        *   @return sf::Texture pointer
        */
      sf::Texture* getTexture(TextureName::TextureName texture);

    private:

      /** Make non-copyable **/
      NON_COPYABLE(TextureLoader);

      std::map<TextureName::TextureName, sf::Texture*> textures;
  };

} // end of namespace UI
