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
    *   @brief DynamicOject inherit class describing static objects in PhysicsWorld
    */
  class StaticObject: public PhysicsObject
  {
    public:
      /**
        *   @brief Constructor for StaticObject
        *   @param shape Shape which matches to the StaticObject
        */
      StaticObject(Shape *shape);
    private:
  };
}// enf of namespace pe
