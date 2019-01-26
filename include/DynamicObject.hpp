/**
  *   @file DynamicObject.hpp
  *   @author Lauri Westerholm
  *   @brief Header for DynamicObject
  */

#pragma once

#include "PhysicsObject.hpp"


/**
  *   @namespace pe
  *   @remark Stands for PhysicsEngine
  */
namespace pe {

  /**
    *   @class DynamicObject
    *   @brief PhysicsWorld dynamic object, inherits PhysicsObject
    */
    class DynamicObject: public PhysicsObject
    {
      public:

        /**
          *   @brief Empty constructor
          */
        DynamicObject();

        /**
          *   @brief Constructor for DynamicOject
          *   @param shape Shape which matches to the DynamicOject
          *   @param density 2D density of the object
          */
        DynamicObject(Shape *shape, float density);

        /**
          *   @brief Set force for DynamicOject
          *   @see PhysicsObject setForce
          *   @details force changes the acceloration value in PhysicsProperties of the object
          *   @param force force to be set for the object
          */
        virtual void setForce(Vector2f force) override;

        /**
          *   @brief Set velocity for DynamicObject
          *   @see PhysicsObject setVelocity
          *   @details velocity replaces old velocity value in PhysicsProperties of the object
          *   @param velocity velocity to be set for the object
          */
        virtual void setVelocity(Vector2f velocity) override;

        /**
          *   @brief Implementation of collisionAction from PhysicsObjects
          *   @details pushes DynamicOject avoid from other object by position_change
          *   @todo Add physics to the implementation
          */
        virtual void collisionAction(Vector2f position_change) override;


    };

}// end of namespace pe
