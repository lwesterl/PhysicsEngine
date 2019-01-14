/**
  *   @file PhysicsProperties
  *   @author Lauri Westerholm
  *   @brief Header for class PhysicsProperties
  */

#pragma once

#include "../utils/Vector2.hpp"
#include <cmath>


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
        static float SizeScale; /**< Scale between shape area to area used in physic calculations, this should be adjusted based on shape sizes used */

        /**
          *   @brief Constructor
          *   @param density object density, 2d-density, (used to calculate mass)
          *   @param static_object pass true if object should be static, by default false
          *   @remark both density and elasticity should be positive (abs is taken)
          */
        PhysicsProperties(float density, float area, bool static_object = false);

        Vector2f velocity; // velocity (x, y)
        Vector2f acceloration; // acceloration (x, y)
        Vector2f force; // force (x, y)
        Vector2f position; // this should be same as the center of mass for the Shape
        float density;
        float elasticity;
        float inverse_mass;

      private:

        /**
          *   @brief Calculate inverse_mass for the object
          *   @param area area of the matching Shape
          *   @param static_object tells whether object is static or not
          *   @details inverse_mass for static_object is set to zero. Calculation is 2D
          *   so density should be also 2D counterpart
          */
        void CalculateInverseMass(float area, bool static_object);
    };



}// end of namespace pe
