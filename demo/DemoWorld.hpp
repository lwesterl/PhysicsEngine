/**
  *   @file DemoWorld.hpp
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
  *   @struct ShapeCMP
  *   @brief Implement comparison for Vector2f which allows to distinguish unique shapes
  */
struct ShapeCMP {
  /**
    *   @brief Comparison used in shapes map
    *   @details std::maps identify correct key by taking negative bools of
    *   comparisons in both orders (!vect1<vect2 and !vect2<vect1)
    *   @param vec1 1st Vector2f to be compared
    *   @param vec2 2nd Vector2f to be compared
    *   @return true if vec1 x or y value is smaller than those of vec2
    */
  bool operator()(const pe::Vector2f& vec1, const pe::Vector2f& vec2) const {
    return (vec1.getX() < vec2.getX()) || (vec1.getY() < vec2.getY());
  }
};

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
      *   @brief Set amount of threads used in the PhysicsWorld instance
      *   @param thread amount of threads
      */
    inline void setThreads(unsigned threads) {
      physWorld.setThreads(threads);
    }

    /**
      *   @brief Get amount of threads used in the PhysicsWorld
      *   @return physWorld.threads
      */
    inline unsigned getThreads() {
      return physWorld.getThreads();
    }

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
      *   @param on true -> collisions on
      */
    void toggleCollisions(bool on);

    /**
      *   @brief Clear PhysicsWorld and delete all DemoObjects
      */
    void clearWorld();

    /**
      *   @brief Load demo level
      *   @param path demo level path, use path provided by DemoLevelLoader::getLevelPath
      */
    void loadDemoLevel(const char* path);

    /**
      *   @brief Set density for all objects in DemoWorld
      *   @param density new density value, see @details
      *   @details This will scale int value to range of [0, 5.f]:
      *   input <= 0: 0.f
      *   input <= 50: 5.f
      *   Thus scaling resolution is 0.1
      *   @remark This should be called via Button in DemoUI MultiChoices
      */
    void setObjectDensity(int density);

    /**
      *   @brief Set elasticity values for all objects
      *   @details This will scale int value to range of [0, 1]:
      *   input <= 0: 0.f
      *   input <= 20: 1.f
      *   Thus scaling resolution is 0.05
      *   @remark This should be called via Button in DemoUI MultiChoices
      *   @param elasticity see @details for scaling
      */
    void setObjectElasticity(int elasticity);


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
    std::map<pe::Vector2f, pe::Shape*, ShapeCMP> shapes;
};
