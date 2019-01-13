/**
  *   @file PhysicsObject.hpp
  *   @author Lauri Westerholm
  *   @brief Header for PhysicsObject
  */


#pragma once

#include "../utils/Vector2.hpp"
#include "../include/Shape.hpp"
#include "../include/PhysicsProperties.hpp"
#include <map>
#include <cstdint>

/**
  *   @namespace pe
  *   @remark Stands for PhysicsEngine
  */
namespace pe {


  /**
    *   @class PhysicsObject
    *   @brief Abstract class for all objects in the PhysicsWorld
    *   @details Class allows to connect an owner object (should be the object used for rest
    *   of the logic, and possibly drawing). Owner object is stored as void pointer and its
    *   type can be stored as int (enum value) for recasting purposes. PhysicsObject won't
    *   delete the owner pointer on deconstructor. This has to be done elsewhere
    */
  class PhysicsObject
  {
    public:
      /**
        *   @brief Constructor
        *   @param position Vector2f position
        *   @mass PhysicsObject mass
        */
      PhysicsObject(Vector2f& position, float density);

      /**
        *   @brief Set owner object
        *   @param owner Owner object casted to void*, use static_cast<void*>
        *   @param type possible object type which may help in recasting (int based enum recommended)
        */
      void setOwner(void* owner, int type=0);
      void* getOwner();
      int getOwnerType();
      void setShape(Shape *shape);
      Shape* getShape();
      PhysicsProperties& getPhysics();
      void setPosition(Vector2f position);
      Vector2f& getPosition();
      void setOriginTransform(Vector2f transform);
      Vector2f& getOriginTransform();




    protected:
      Shape *shape = nullptr; // polygonshape
      Vector2f origin_transform; /**< Transform from object center of mass to user defined point */
      PhysicsProperties physics;
      std::map<void*, int> owner;
      uint16_t collision_mask; // used to detect collisions


  };
} // end of namespace pe
