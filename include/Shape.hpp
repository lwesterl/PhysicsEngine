/**
  *   @file Shape.hpp
  *   @author Lauri Westerholm
  *   @brief Header for Shape
  */


#pragma once

#include "../utils/Vector2.hpp"
#include <deque>
#include <cmath>

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
          *   @param width box width
          *   @param height box height
          *   @remark width and height should be > 0 (abs is taken)
          */
        Shape(float width, float height);

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
          *   @brief Get min
          *   @return Vector2f matching min
          *   @details Returns an empty pe::Vector2f if min is nullptr
          */
        Vector2f getMin();

        /**
          *   @brief Get max
          *   @return Vector2f matching max
          *   @details Returns an empty pe::Vector2f if max is nullptr
          */
        Vector2f getMax();

        /**
          *   @brief Get area of the Shape
          *   @return area
          */
        float getArea();


      private:

        /**
          *   @brief Search through frame to find min and max Vector2fs
          *   @details Sets pointer to correct frame indexes
          */
        void FindMinMax();

        /**
          *   @brief Calculate polygon center of mass
          *   @details assigns center of mass to mass_center. Uses basic formula which defines
          *   centroid for polygon shapes. Calculates also area of Shape
          */
        void CenterMass();


        Vector2f mass_center; /**< This should be object mass center point */
        std::deque<Vector2f> frame; /**< Object frame, polygon of connected Vector2f */
        Vector2f* max = nullptr; /**< Should point to the biggest entry in frame */
        Vector2f* min = nullptr; /**< Should point to the smallest entry in frame */
        float area; /**< Area of the Spape */

    };
}// end of namespace pe
