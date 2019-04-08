/**
  *   @file DemoLevelLoader.cpp
  *   @author Lauri Westerholm
  *   @brief Source for all level loading related functions and data structures
  */

#include "DemoLevelLoader.hpp"

namespace DemoLevelLoader {

  std::map<const char*, const char*, STRCMP> LevelNameToPath =
  {
    { "Demo: flat ground", "demo_levels/flat_ground.csv" },
    { "Demo: downward slope", "demo_levels/downward_slope.csv" },
    { "Demo: half circle", "demo_levels/half_circle.csv" },
    { "Demo: many objects", "demo_levels/many_objects.csv" }
  };

  std::list<const char*> LevelNames =
  {
    "Demo: flat ground",
    "Demo: downward slope",
    "Demo: half circle",
    "Demo: many objects"
  };

  const char* StartLevel = "Demo: flat ground";
  const int StartLevelIndex = 0;

}
