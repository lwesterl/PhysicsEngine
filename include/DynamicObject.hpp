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
          *   @brief Constructor for DynamicOject
          *   @param shape Shape which matches to the DynamicOject
          *   @param density 2D density of the object
          */   
        DynamicObject(Shape *shape, float density);

      private:
    };

}// end of namespace pe
