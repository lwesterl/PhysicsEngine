/**
  *   @file CollisionDetection.cpp
  *   @author Lauri Westerholm
  *   @brief Contains implementations relating to CollisionDetection
  */

#include "../include/CollisionDetection.hpp"
#include <iostream>


namespace pe {

  namespace CollisionDetection {

    // Calculate possible collision between objects
    bool calculateCollision(PhysicsObject* obj1, PhysicsObject* obj2) {

      // check if objects are even relatively close to one another
      if (!objectsClose(obj1, obj2)) return false;

      // objects could collide, calculate possible collisions
      Shape* shape1 = obj1->getShape();
      Shape* shape2 = obj2->getShape();
      // for obj1 axis
      std::vector<Vector2f>& axis = shape1->getAxis();
      for (int i = 0; i < shape1->getEdges(); i++) {
        // project both Shapes
        // TODO replace 0.f with correct angle
        struct Projection proj1 = ProjectShape(axis[i], obj1->getPhysics().position, shape1, 0.f);
        struct Projection proj2 = ProjectShape(axis[i], obj2->getPhysics().position, shape2, 0.f);
        if (! overlap(proj1, proj2)) return false; // one projection which won't overlap is enough
      }
      // for obj2 axis
      axis = shape2->getAxis();
      for (int i = 0; i < shape2->getEdges(); i++) {
        // project both Shapes
        // TODO replace 0.f with correct angle
        struct Projection proj1 = ProjectShape(axis[i], obj1->getPhysics().position, shape1, 0.f);
        struct Projection proj2 = ProjectShape(axis[i], obj2->getPhysics().position, shape2, 0.f);
        if (! overlap(proj1, proj2)) return false; // one projection which won't overlap is enough
      }
      // all projections overlap, collision detected
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

    // Project Shape on axis
    struct Projection ProjectShape(Vector2f axis, Vector2f position, Shape* shape, float object_angle) {
      // init min and max
      float min = std::numeric_limits<float>::max();
      float max = std::numeric_limits<float>::min();
      std::deque<Vector2f> edges = shape->getFrame();
      for (int i = 0; i < shape->getEdges(); i++) {
        // edge[i] is just a static point, position tells where it's relating to PhysicsWorld origin
        Vector2f edge = edges[i] + position;
        edge.rotate(object_angle); // rotate to angle matching PhysicsObject angle
        float dot = dotProduct(axis, edge);
        if (dot < min) min = dot;
        if (dot > max) max = dot;
      }
      struct Projection projection;
      projection.min = min;
      projection.max = max;
      return projection;
    }

    // Check if Projections overlap
    bool overlap(struct Projection& proj1, struct Projection& proj2) {
      return !(proj1.max < proj2.min || proj2.max < proj1.min);
    }

  }// end of namespace CollisionDetection
}// end of namespace pe
