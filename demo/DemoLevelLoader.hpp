/**
  *   @file DemoLevelLoader.hpp
  *   @author Lauri Westerholm
  *   @brief Header for demo level loading related data structures
  */

#pragma once
#include <map>
#include <list>
#include <cstring>

/**
  *   @namespace DemoLevelLoader
  *   @brief Contains all level loading related data structures
  */
namespace DemoLevelLoader {

  /**
    *   @struct STRCMP
    *   @brief For LevelNameToPath comparisons
    */
  struct STRCMP {
    /**
      *   @brief Comparison function needed for LevelNameToPath
      *   @param str1 1st cstring to be compared
      *   @param str2 2nd cstring to be compared
      */
    bool operator()(const char* str1, const char* str2) const {
      return std::strcmp(str1, str2) < 0;
    }
  };
  extern std::map<const char*, const char*, STRCMP> LevelNameToPath; /**< level names as keys to mathing file paths */
  extern std::list<const char*> LevelNames; /**< all the level names */
  extern const char* StartLevel; /**< start level in demo */
  extern const int StartLevelIndex; /**< matching index for StarLevel and LevelNames */

  /**
    *   @brief Get level path
    *   @param levelName needs to be valid level name in LevelNames
    */
  inline const char* getLevelPath(const char* levelName) {
    return LevelNameToPath[levelName];
  }

} // end of namespace DemoLevelLoader
