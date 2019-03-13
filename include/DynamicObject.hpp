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
          *   @brief Constructor for DynamicObject
          *   @param shape Shape which matches to the DynamicObject
          *   @param density 2D density of the object
          */
        DynamicObject(Shape *shape, float density);

        /**
          *   @brief Set force for DynamicObject
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
          *   @details pushes DynamicObject avoid from other object by position_change
          *   @todo Physics could be tuned
          */
        virtual void collisionAction(Vector2f position_change) override;

        /**
          *   @brief Implementation of updatePhysics from PhysicObject
          *   @details Updates DynamicObject PhysicsProperties, physics, based
          *   on elapsed_time
          *   @param elapsed_time time elapsed from the last update (in seconds)
          *   @remark Gravity needs to be high value to make objects fall fast ->
          *   some scaling number could be used to make more realistic gravity values
          *   suitable
          */
        virtual void updatePhysics(float elapsed_time) override;


      private:
        Vector2f inverse_direction_unit_vector; /**< Unit vector ponting to the opposite direction than current movement */


    };

}// end of namespace pe
