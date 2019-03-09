/**
  *   @file World.hpp
  *   @author Lauri Westerholm
  *   @brief Header for demo DemoWorld
  */


#pragma once
#include "../include/PhysicsWorld.hpp"
#include "DemoObject.hpp"
#include <SFML/Graphics.hpp>


/**
  *   @class DemoWorld
  *   @brief World for DemoObjects
  */
class DemoWorld
{
  public:
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
      */
    int handleEvent(sf::Event &event);

    /**
      *   @brief Update DemoObjects positions etc.
      */
    void update();

    /**
      *   @brief Draw all DemoObjects in the world
      */
    void draw();

  private:
    sf::RenderWindow &window;
    pe::PhysicsWorld physWorld;
    pe::Shape *shape; /**< this will be replaced by a proper Shape allocator */
};
