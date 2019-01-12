/**
  *   @file Shape.hpp
  *   @author Lauri Westerholm
  *   @brief Header for Shape
  */


#pragma once

#include "../utils/Vector2.hpp"
#include <deque>

/**
  *   @namespace pe
  *   @remark Stands for PhysicsEngine
  */
namespace pe {
  /**
    *   @class Shape
    *   @brief Contains PhysicsObject shape (polygon)
    *   @details Shapes are implemented such a way that they can be reused for multiple
    *   PhysicsObjects (same style PhysicsObjects can share same Shape pointer)
    */
    class Shape
    {
      public:
        /**
          *   @brief Empty constructor
          *   @details Creates an empty shape
          */
        Shape();

        /**
          *   @brief Constructor for box shape
          *   @param left_upper position of the box left upper corner
          *   @param width box width
          *   @param height box height
          */
        Shape(Vector2f left_upper, float width, float height);

        /**
          *   @brief Copy constructor
          *   @param shape Shape to be copied
          */
        Shape(const Shape& shape);

        /**
          *   @brief Assignment overload
          *   @param shape shape to be copied
          *   @return Shape which is identical to shape
          */
        Shape& operator=(const Shape& shape);

        /**
          *   @brief Get the center of mass of Shape
          *   @return reference to mass_center
          */
        Vector2f& getCenter();

        /**
          *   @brief Get the Shape frame
          *   @return frame as constant reference
          */
        const std::deque<Vector2f>& getFrame();

        /**
          *   @brief Check whether a point is inside shape or not
          *   @param point to be checked
          *   @return true if point is inside, otherwise false
          */
        bool isInside(Vector2f& point);


      private:

        /**
          *   @brief Calculate polygon center of mass
          *   @details assigns center of mass to mass_center. Uses basic formula which defines
          *   centroid for polygon shapes
          */
        void CenterMass();


        Vector2f mass_center; /**< This should be object mass center point */
        std::deque<Vector2f> frame; /**< Object frame, polygon of connected Vector2f */
        Vector2f* max = nullptr; /**< Should point to the biggest entry in frame */
        Vector2f* min = nullptr; /**< Should point to the smallest entry in frame */

    };
}// end of namespace pe
