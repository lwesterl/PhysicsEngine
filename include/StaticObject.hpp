/**
  *   @file StaticObject.hpp
  *   @author Lauri Westerholm
  *   @brief Header for StaticObject
  */

#pragma once

#include "PhysicsObject.hpp"

/**
  *   @namespace pe
  *   @remark Stands for PhysicsEngine
  */
namespace pe {

  /**
    *   @class StaticObject
    *   @brief PhysicsObject inherited class describing static objects in PhysicsWorld
    */
  class StaticObject: public PhysicsObject
  {
    public:

      /**
        *   @brief Empty constructor
        */
        StaticObject();

      /**
        *   @brief Constructor for StaticObject
        *   @param shape Shape which matches to the StaticObject
        */

      StaticObject(Shape *shape);

      /**
        *   @brief setForce implementation, no force can be set for StaticObject
        *   @param force not used but this way same function call can be kept
        */
      virtual void setForce(__attribute__((unused)) Vector2f force) override {}

      /**
        *   @brief setVelocity implementation, no velocity can be set for StaticObject
        *   @param velocity not used but this way same function call can be kept
        */
      virtual void setVelocity(__attribute__((unused)) Vector2f velocity) override {}

      /**
        *   @brief collisionAction implementation, no collision action for StaticObject
        *   @param position_change not used, needed to override PhysicsObject collisionAction
        */
      virtual void collisionAction(__attribute__((unused)) Vector2f position_change) override {}

      /**
        *   @brief updatePhysics implementation, no active physics for StaticObject
        *   @param elapsed_time not used, needed to override PhysicsObject updatePhysics
        */
      virtual void updatePhysics(__attribute__((unused)) float elapsed_time) override {}

  };
}// enf of namespace pe
