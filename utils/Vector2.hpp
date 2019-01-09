/**
  *   @file Vector2.hpp
  *   @brief Vector2 Header
  *   @details Contains class for representing 2D-vectors
  */

#pragma once

#include <ostream>

/**
  *   @class Vector2
  *   @brief Template class for 2D-vectors
  */

template <typename T>
class Vector2
{
  public:
    /**
      *   @brief Standard constructor
      *   @param x x coordinate
      *   @param y y coordinate
      */
    Vector2(T x, T y);

    /**
      *   @brief Copy constructor
      *   @param vector2 Vector2 instance to be copied
      */
    Vector2(const Vector2<T>& vector2);

    /**
      *   @brief Assignment operator
      *   @param vector2 Reference instance
      */
    Vector2<T>& operator=(const Vector2<T>& vector2);

    /**
      *   @brief Get x value
      *   @return x
      */
    inline T getX();

    /**
      *   @brief Get y value
      *   @return y
      */
    inline T getY();

    /**
      *   @brief <<-operator overload
      *   @param os output ostream
      *   @param vector2 Constant Vector2 instance
      */
    friend std::ostream& operator<<(std::ostream &os, const Vector2<T> &vector2) {
      os << "X: " << vector2.x << ", Y: " << vector2.y << std::endl;
      return os;
    }


  private:
    T x;
    T y;
};

/*  Define shorter keyword */
#define Vector2f Vector2<float> /**< Macro for float Vector2 */
#define Vector2i Vector2<int> /**< Macro for int Vector2 */
#define Vector2d Vector2<double> /**< Macro for double Vector2 */
#define Vector2u Vector2<unsigned> /**< Macro for unsigned Vector2 */
