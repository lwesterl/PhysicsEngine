/**
  *   @file PhysicsProperties
  *   @author Lauri Westerholm
  *   @brief Header for class PhysicsProperties
  */

#pragma once

#include "../utils/Vector2.hpp"


namespace pe {

  /**
    *   @class PhysicsProperties
    *   @brief Holds all physics related properties of PhysicsObject
    *   @details Positive coordinate direction is downwards (i.e. upwards is the negative direction)
    *   In x-dimension the coordinate system has standard cartesian directions (right -> +, left -> -)
    *   This class is used as a storing class for physics related variables -> variables should be publicly accessible
    */
    class PhysicsProperties
    {
      public:
        /*  Member variables */
        static float GravityX; /**< X dimansional gravity (- left) */
        static float GravityY; /**< Y dimansional gravity (- upwards) */

        /**
          *   @brief Constructor
          *   @param density object density (used to calculate mass)
          */
        PhysicsProperties(float density, float elasticity);

        Vector2f velocity; // velocity (x, y)
        Vector2f acceloration; // acceloration (x, y)
        Vector2f force; // force (x, y)
        Vector2f position; // this should be same as the center of mass for the Shape
        float density;
        float elasticity;
        float inverse_mass;

      private:

        void CalculateInverseMass();
    };



}// end of namespace pe
