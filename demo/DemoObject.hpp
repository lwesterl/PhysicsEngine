/**
  *   @file DemoObject.hpp
  *   @author Lauri Westerholm
  *   @brief Header for objects used in DemoWorld
  */

#pragma once

#include "../include/PhysicsObject.hpp"
#include "../include/DynamicObject.hpp"
#include "../include/StaticObject.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderStates.hpp>


/**
  *   @class DemoObject
  *   @brief Class for object which are used to demo PhysicsEngine
  *   @details DemoObject uses SFML to provide framework for rendering
  */
class DemoObject: sf::Drawable
{
  public:
    /**
      *   @brief Empty constructor
      */
    DemoObject();

    /**
      *   @brief Create DemoObject which is either dynamic or static
      *   @param type pe::ObjectType specifies whether object is static or dynamic
      *   @param shape pointer to Shape used for PhysicsObject and sf::RectangleShape
      *   @param color DemoObject color
      */
    DemoObject(pe::ObjectType::ObjectType type, pe::Shape* shape, sf::Color color);

    /**
      *   @brief Copy constructor
      *   @param demoObject DemoObject to be copied
      */
    DemoObject(const DemoObject& demoObject);

    /**
      *   @brief Assignment operator
      *   @param demoObject DemoObject to be assigned
      *   @details Shape is passed as soft copy (same pointer) whereas physicsObject
      *   is a hard-copy (new object).
      *   NOTICE: Use this method very carefully, this does NOT delete memory allocated
      *   for physicsObject:
      *   1. physicsObject is nullptr -> safe to use
      *   2. physicsObject added to pe::PhysicsWorld -> call pe::PhysicsWorld::removeObject(physicsObject) prior replacement
      *   3. physicsObject not added to pe::PhysicsWorld -> delete physicsObject elsewhere
      */
    DemoObject& operator=(const DemoObject& demoObject);

    /**
      *   @brief Deconstructor
      *   @details DOES NOT delete memory allocated for shape nor physicsObject
      *   PhysicsObject should be deleted by pe::PhysicsWorld and shape by DemoWorld
      *   or external pe::Shape allocator
      */
    virtual ~DemoObject() {}

    /**
      *   @brief Draw DemoObject
      *   @details Method inherited from sf::Drawable
      *   @param target sf::RenderTarget
      *   @param states sf::RenderStates
      */
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    /**
      *   @brief Set DemoObject position
      *   @param x new x coordinate
      *   @param y new y coordinate
      */
    void setPosition(float x, float y);

    /**
      *   @brief Set DemoObject color
      *   @param color new sf::Color
      */
    void setColor(sf::Color color);

    /**
      *   @brief Get PhysicsObject pointer
      *   @return physicsObject
      */
    inline pe::PhysicsObject* getPhysicsObject() {
      return physicsObject;
    }

  private:
    /**
      *   @brief Copy another DemoObject
      *   @param demoObject DemoObject to be copied
      */
    void Copy(const DemoObject& demoObject);

    pe::PhysicsObject* physicsObject;
    sf::RectangleShape rectShape;
};
