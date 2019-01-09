/**
  *   @file Vector2.cpp
  *   @brief Source code for class Vector2
  */

#include "Vector2.hpp"


/*  Constructors */
template<typename T>
Vector2<T>::Vector2(T x, T y): x(x), y(y) {}

template<typename T>
Vector2<T>::Vector2(const Vector2<T>& vector2): x(vector2.x), y(vector2.y) {}

template<typename T>
Vector2<T>& Vector2<T>::operator=(const Vector2<T>& vector2) {
  this->x = vector2.x;
  this->y = vector2.y;
  return *this;
}

template<typename T>
T Vector2<T>::getX() {
  return x;
}

template<typename T>
T Vector2<T>::getY() {
  return y;
}

/*  Instantiate needed templates */
template class Vector2<int>;
template class Vector2<float>;
template class Vector2<unsigned>;
template class Vector2<double>;
