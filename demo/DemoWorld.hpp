/**
  *   @file World.hpp
  *   @author Lauri Westerholm
  *   @brief Header for demo DemoWorld
  */


#pragma once
#include "../include/PhysicsWorld.hpp"
#include "DemoObject.hpp"
#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>


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
    void handleEvent(sf::Event &event);

    /**
      *   @brief Update DemoObjects positions etc.
      */
    void update();

    /**
      *   @brief Draw all DemoObjects in the world
      */
    void draw();

  private:
    /**
      *   @brief Try to move DemoObject
      *   @param event SFML MouseMove event
      */
    void MouseMove(sf::Event& event);

    /**
      *   @brief Try to activate DemoObject
      *   @param event SFML MouseButtonPressed event
      */
    void MousePress(sf::Event& event);

    sf::RenderWindow &window;
    pe::PhysicsWorld physWorld;
    pe::Shape *shape; /**< this will be replaced by a proper Shape allocator */
    std::list<DemoObject*> demoObjects;
};
