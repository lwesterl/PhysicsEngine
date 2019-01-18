/**
  *   @file PhysicsObject.hpp
  *   @author Lauri Westerholm
  *   @brief Header for PhysicsObject
  */


#pragma once

#include "../utils/Vector2.hpp"
#include "../include/Shape.hpp"
#include "../include/PhysicsProperties.hpp"
#include <cmath>
#include <utility>
#include <cstdint>

/**
  *   @namespace pe
  *   @remark Stands for PhysicsEngine
  */
namespace pe {


  /**
    *   @namespace ObjectType
    *   @brief Used just to avoid namespace collisions between DynamicOject and StaticObject
    */
  namespace ObjectType {

    /**
      *   @enum ObjectType
      *   @brief Tells whether PhysicsObject is DynamicObject or StaticObject
      */
    enum ObjectType {
      DynamicObject, /**< DynamicObject */
      StaticObject  /**< StaticObject */
    };
  } // end of namespace ObjectType


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
        *   @brif Empty constructor
        */
        PhysicsObject() {}

      /**
        *   @brief Constructor
        *   @param shape matching Shape (pass valid Shape, otherwise causes segmentation violation)
        *   @param density tells object 2D density, used in calculating mass
        *   @param static_object tells whether object is static or not
        *   @param type Object type (passed by lower class constructor, DynamicOject / StaticObject)
        *   @details Constructs PhysicsProperties based on the density and Shape
        */
      PhysicsObject(Shape *shape, float density, bool static_object, ObjectType::ObjectType type);

      /**
        *   @brief Set owner object
        *   @param owner Owner object casted to void*, use static_cast<void*>
        *   @param type possible object type which may help in recasting (int based enum recommended)
        */
      void setOwner(void* owner, int type=0);

      /**
        *   @brief Get owner
        *   @return owner (void *, must be recasted)
        */
      void* getOwner();

      /**
        *   @brief Get owner type
        *   @return owner type stored as an int value
        */
      int getOwnerType();

      /**
        *   @brief Get Shape
        *   @return shape (Shape*)
        */
      Shape* getShape();

      /**
        *   @brief Get PhysicsProperties of the object
        *   @return physics as reference
        */
      PhysicsProperties& getPhysics();

      /**
        *   @brief Set position for object
        *   @param position new physics.position
        *   @details position is normally calculated in relation to Shape center of mass.
        *   setOriginTransform to choose arbitrary base point for position
        */
      void setPosition(Vector2f position);

      /**
        *   @brief Get PhysicsObject position
        *   @return physics.position
        */
      Vector2f& getPosition();

      /**
        *   @brief Set origin transform
        *   @details PhysicsObject position is normally calculated in relation to shape
        *   center of mass. Use setOriginTransform to move the base point for position related
        *   calculation. e.g. want to move object from its left upper corner, set transform to be
        *   Vector2f from the shape center to the left upper corner.
        *   @param transform positive x values moves object origin to right and positive y values
        *   downwards
        */
      void setOriginTransform(Vector2f transform);

      /**
        *   @brief Get current origin transform
        *   @return physics.origin_transform
        *   @see setOriginTransform
        */
      Vector2f& getOriginTransform();

      /**
        *   @brief Set elasticity for PhysicsObject
        *   @details By default elasticity is set to 0.9 in PhysicsProperties. Use
        *   this to adjust bounciness of the object: higher values -> more bounciness
        */
      void setElasticity(float elasticity);

      /**
        *   @brief Get elasticity of PhysicsObject
        *   @return physics.elasticity
        */
      float getElasticity();



    protected:
      Shape *shape = nullptr; /**< Shape matching PhysicsObject, polygon */
      PhysicsProperties physics;  /**< PhysicsProperties of PhysicsObject */
      std::pair<void*, int> owner; /**< Pair made out of owner object and possible int type used for it */
      uint16_t collision_mask; /**< Bitmask used in collision detection */
      ObjectType::ObjectType type;  /**< PhysicsObject type, either DynamicOject or StaticObject */


  };
} // end of namespace pe