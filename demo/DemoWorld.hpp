/**
  *   @file World.hpp
  *   @author Lauri Westerholm
  *   @brief Header for demo DemoWorld
  */


#pragma once
#include "../include/PhysicsWorld.hpp"
#include "DemoObject.hpp"
#include "DemoLevelLoader.hpp"
#include <SFML/Graphics.hpp>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


/**
  *   @class DemoWorld
  *   @brief World for DemoObjects
  */
class DemoWorld
{
  public:

    /**
      *   @brief Set x dimensional gravity, static
      *   @param gravity new gravity value as int
      */
    static void setGravityX(int);

    /**
      *   @brief Set y dimensional gravity, static
      *   @param gravity new gravity value as int
      */
    static void setGravityY(int);

    /**
      *   @brief Constructor for DemoWorld
      *   @param window active SFML RenderWindow
      */
    DemoWorld(sf::RenderWindow& window);

    /**
      *   @brief Deconstructor
      */
    virtual ~DemoWorld();

    /**
      *   @brief Create initial DemoWorld
      *   @details Inits and creates all GraphicsObjects
      */
    void initWorld();

    /**
      *   @brief Handle incoming events
      *   @param event SFML event
      *   @return DemoObject pointer which was activated, otherwise nullptr
      */
    DemoObject* handleEvent(sf::Event &event);

    /**
      *   @brief Update DemoObjects positions etc.
      */
    void update();

    /**
      *   @brief Draw all DemoObjects in the world
      */
    void draw();

    /**
      *   @brief Toggle object removal on/off
      *   @details This should be called from DemoUI
      */
    inline void toggleObjectRemoval() {
      removeCollided ? removeCollided = false: removeCollided = true;
    }

    /**
      *   @brief Toggle object collisions on/off
      *   @details This should be called from DemoUI
      */
    void toggleCollisions();

    /**
      *   @brief Clear PhysicsWorld and delete all DemoObjects
      */
    void clearWorld();

    /**
      *   @brief Load demo level
      *   @param path demo level path, use path provided by DemoLevelLoader::getLevelPath
      */
    void loadDemoLevel(const char* path);


  private:

    /**
      *   @brief Try to activate DemoObject
      *   @param event SFML MouseButtonPressed event
      *   @return DemoObject which was pressed, otherwise nullptr
      */
    DemoObject* MousePress(sf::Event& event);

    /**
      *   @brief Remove collided PhysicsObjects and DemoObjects
      *   @param collide struct containg collided PhysicsObject pointer
      */
    void RemoveCollided(struct pe::Collided& collided);

    /**
      *   @brief Convert std::string to pe::ObjectType::ObjectType
      *   @param str string that should be either "DynamicObject" or "StaticObject"
      *   @return matching pe::ObjectType
      */
    pe::ObjectType::ObjectType StrToObjectType(std::string& str) const;

    /**
      *   @brief Get correct shape
      *   @details If shape already exits, returns pointer to it. Otherwise this
      *   will create the required pe::Shape
      *   @return pe::Shape with correct size
      */
    pe::Shape* GetShape(float width, float height);

    sf::RenderWindow &window;
    pe::PhysicsWorld physWorld;
    std::list<DemoObject*> demoObjects;
    bool removeCollided;
    bool collisions;
    std::map<pe::Vector2f, pe::Shape*> shapes;
};
