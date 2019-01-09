/**
  *   @file Vector2_test.cpp
  *   @brief Test main for Vector2 class
  */



#include "../utils/Vector2.hpp"
#include <iostream>
#include <assert.h>

/**
  *   @brief Test main
  */

int main() {
  Vector2i vect = Vector2i(3, 10);
  std::cout << vect;
  return 0;
}
