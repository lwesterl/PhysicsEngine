/**
  *   @file CollisionDetection.hpp
  *   @author Lauri Westerholm
  *   @brief Contains collision detection related function definitions
  *   @details functions are under namespace pe::CollisionDetection
  */

#pragma once

#include "../utils/Vector2.hpp"
#include "PhysicsObject.hpp"
#include "PhysicsProperties.hpp"


/**
  *   @namespace pe
  *   @remark Stands for PhysicsEngine
  */
namespace pe {

  /**
    *   @namespace CollisionDetection
    *   @brief Contains all collision detection related functions
    *   @details These functions should be called periodically from PhysicsWorld
    */
  namespace CollisionDetection {

    /**
      *   @brief Calculate collision between PhysicsObjects
      *   @details Check if objects have collided and apply necessary forces to the
      *   objects to separate them
      *   @param obj1 1st PhysicsObject to be checked
      *   @param obj2 2nd PhysicsObject to be checked
      *   @return true if obj1 and obj2 collided, else false
      *   @remark This is the function which provides interface for collision detection
      *   and should be called from PhysicsWorld
      */
    bool calculateCollision(PhysicsObject* obj1, PhysicsObject* obj2);

    /**
      *   @brief Check if objects are close to each other
      *   @details This functions should tell whether objects could collide with each other.
      *   So it tells whether further calculations need to be made. The idea is to detect
      *   a situation where objects cannot collide asap: then there is no need to make
      *   more precise calculations
      *   @param obj1 1st PhysicObject to be checked
      *   @param obj2 2nd PhysicsObject to be checked
      *   @return true if objects could collide, else false
      */
    bool objectsClose(PhysicsObject* obj1, PhysicsObject* obj2);



  } // end of namespace CollisionDetection
} // end of namespace pe
