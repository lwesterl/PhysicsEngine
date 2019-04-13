### Demo
* Graphics are created using SFML
* Uses PhysicsEngine, libphysengine, for physics

## Makefile

Command | Description
--------|-------------
make                | compile all objects and demo
make run            | compile all and run demo
make clean          | remove all objects, demo and library
make clean-objects  | remove all objects from demo folder

Note: PhysicsEngine related objects are created to src and utils folders

## Notes
* demo.cpp is the entry point but central class is DemoUI
* UI related classes can be found from UI-elements
___
* Demo levels are located in demo_levels
* Levels use .csv-format and further format specs are in demo_levels/demo_level_info.txt
* Levels can be added to demo_levels. However, then DemoLevelLoader (DemoLevelLoader.cpp) 'LevelNameToPath' and 'LevelNames' data structures need to be updated to contain the new levels.
