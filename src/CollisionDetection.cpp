/**
  *   @file CollisionDetection.cpp
  *   @author Lauri Westerholm
  *   @brief Contains implementations relating to CollisionDetection
  */

#include "../include/CollisionDetection.hpp"


namespace pe {

  namespace CollisionDetection {

    // Calculate possible collision between objects
    bool calculateCollision(PhysicsObject* obj1, PhysicsObject* obj2) {

      // check if objects are even relatively close to one another
      if (!objectsClose(obj1, obj2)) return false;

      // objects could collide, calculate possible collisions
      return true;
    }

    //  Check if PhysicsObjects are close
    bool objectsClose(PhysicsObject* obj1, PhysicsObject* obj2) {

      PhysicsProperties& physics1 = obj1->getPhysics();
      PhysicsProperties& physics2 = obj2->getPhysics();
      Vector2f min1 = obj1->getShape()->getMin() + physics1.position;
      Vector2f max1 = obj1->getShape()->getMax() + physics1.position;
      Vector2f min2 = obj2->getShape()->getMin() + physics2.position;
      Vector2f max2 = obj2->getShape()->getMax() + physics2.position;

      // check if min and maxes overlap
      if ( ((max1.getX() < min2.getX()) && (max1.getX() + physics1.velocity.getX() < min2.getX())) ||
            ((min1.getX() > max2.getX()) && (min1.getX() + physics1.velocity.getX() > max2.getX())) ) return false;

      if ( ((max1.getY() < min2.getY()) && (max1.getY() + physics1.velocity.getY() < min2.getY())) ||
            ((min1.getY() > max2.getY()) && (min1.getY() + physics1.velocity.getY() > max2.getY())) ) return false;

      return true;
    }

  }// end of namespace CollisionDetection
}// end of namespace pe
