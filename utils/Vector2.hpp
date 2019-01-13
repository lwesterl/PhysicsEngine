/**
  *   @file Vector2.hpp
  *   @author Lauri Westerholm
  *   @brief Vector2 Header
  *   @details Contains class for representing 2D-vectors
  */

#pragma once

#include <ostream>

/**
  *   @namespace pe
  *   @remark Stands for PhysicsEngine
  */
namespace pe {

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
        *   @brief Empty constructor
        *   @remark sets x and y to 0
        */
      Vector2();

      /**
        *   @brief Copy constructor
        *   @param vector2 Vector2 instance to be copied
        */
      Vector2(const Vector2<T>& vector2);

      /**
        *   @brief Get x value
        *   @return x
        */
      T getX();

      /**
        *   @brief Get y value
        *   @return y
        */
      T getY();

      /**
        *   @brief Update x and y values
        *   @param x new x value
        *   @param y new y value
        */
      void update(T x, T y);

      /**
        *   @brief Dot product for Vector2
        *   @param vector another Vector2 in relation dot product is calculated
        *   @return dot product of the vectors
        *   @remark dotProduct also available as external function
        */
      float dotProduct(const Vector2<T>& vector);

      /**
        *   @brief Assignment operator
        *   @param vector2 Reference instance
        */
      Vector2<T>& operator=(const Vector2<T>& vector2);

      /**
        *   @brief Multiplication by number
        *   @param mult multiplier
        *   @return updated Vector2 refence
        */
      Vector2<T>& operator*=(T mult);

      /**
        *   @brief Equality implementation
        *   @param vect1 the first passed Vector2
        *   @param vect2 the second passed Vector2
        *   @return true if x and y equal, otherwise false
        */
      friend bool operator==(const Vector2<T>& vect1, const Vector2<T>& vect2) {
        return ( (vect1.x == vect2.x) && (vect1.y == vect2.y) );
      }

      /**
        *   @brief Greater than overload
        *   @param vect1 the first passed Vector2
        *   @param vect2 the second passed Vector2
        *   @return true if vect1 x and y are greater than those of vect2
        */
      friend bool operator>(const Vector2<T>& vect1, const Vector2<T>& vect2) {
        return ( (vect1.x > vect2.x) && (vect1.y > vect2.y) );
      }

      /**
        *   @brief Less than overload
        *   @param vect1 the first passed Vector2
        *   @param vect2 the second passed Vector2
        *   @return true if vect1 x and y are less than those of vect2
        */
      friend bool operator<(const Vector2<T>& vect1, const Vector2<T>& vect2) {
        return ( (vect1.x < vect2.x) && (vect1.y < vect2.y) );
      }

      /**
        *   @brief Greater than or equal to overload
        *   @param vect1 the first passed Vector2
        *   @param vect2 the second passed Vector2
        *   @return true if vect1 x and y are greater or equal than those of vect2
        */
      friend bool operator>=(const Vector2<T>& vect1, const Vector2<T>& vect2) {
        return ( (vect1.x >= vect2.x) && (vect1.y >= vect2.y) );
      }

      /**
        *   @brief Less than or equal to overload
        *   @param vect1 the first passed Vector2
        *   @param vect2 the second passed Vector2
        *   @return true if vect1 x and y are less than or equal to those of vect2
        */
      friend bool operator<=(const Vector2<T>& vect1, const Vector2<T>& vect2) {
        return ( (vect1.x <= vect2.x) && (vect1.y <= vect2.y) );
      }

      /**
        *   @brief multiplication overload
        *   @param vect1 the first passed Vector2
        *   @param vect2 the second passed Vector2
        *   @return Vector2 which is original vectors multiplied
        */
      friend Vector2<T> operator*(const Vector2<T>& vect1, const Vector2<T>& vect2) {
        return Vector2<T>(vect1.x * vect2.x, vect1.y * vect2.y);
      }

      /**
        *   @brief addition overload
        *   @param vect1 the first passed Vector2
        *   @param vect2 the second passed Vector2
        *   @return Vector2 which is sum of the original vectors
        */
      friend Vector2<T> operator+(const Vector2<T>& vect1, const Vector2<T>& vect2) {
        return Vector2<T>(vect1.x + vect2.x, vect1.y + vect2.y);
      }

      /**
        *   @brief <<-operator overload
        *   @param os output ostream
        *   @param vector2 Constant Vector2 instance
        */
      friend std::ostream& operator<<(std::ostream &os, const Vector2<T> &vector2) {
        os << "X: " << vector2.x << ", Y: " << vector2.y << std::endl;
        return os;
      }

      /**
        *   @brief Function implementation for dotproduct
        *   @param vect1 1st Vector2
        *   @param vect2 2nd Vector2
        *   @return dot product of the vectors
        *   @remark dotProduct also available as member method
        */
      friend float dotProduct(const Vector2<T>& vect1, const Vector2<T>& vect2) {
        return vect1.x * vect2.x + vect1.y * vect2.y;
      }


    private:
      T x;
      T y;
  };

  /*  Define shorter keywords */
  #define Vector2f Vector2<float> /**< Macro for float Vector2 */
  #define Vector2i Vector2<int> /**< Macro for int Vector2 */
  #define Vector2d Vector2<double> /**< Macro for double Vector2 */
  #define Vector2u Vector2<unsigned> /**< Macro for unsigned Vector2 */

} // end of namespace pe
