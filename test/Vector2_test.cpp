/**
  *   @file Vector2_test.cpp
  *   @author Lauri Westerholm
  *   @brief Test main for Vector2 class
  */



#include "../utils/Vector2.hpp"
#include <iostream>
#include <cassert>

/**
  *   @brief Test main
  */

int main() {

  // constructor test
  std::cout << "Constructor Test" << std::endl;
  pe::Vector2f vectf(3.f, 10.f);
  pe::Vector2f vectf2 = pe::Vector2<float>(3.00, 10.000);
  pe::Vector2u vector2u;
  assert(vector2u.getX() == 0 && vector2u.getY() == 0);
  vector2u = pe::Vector2u(200, 100);
  std::cout << vector2u;
  std::cout << vector2u;
  assert(vectf == vectf2);
  pe::Vector2f vectf3 = vectf2;
  assert(vectf3 == vectf2);
  std::cout << "Test successful" << std::endl;


  // getX and getY test
  std::cout << std::endl << "getX() and getY() test" << std::endl;
  pe::Vector2d test1(10.00, 100.00);
  pe::Vector2d test2 = pe::Vector2d(test1.getX(), test1.getY());
  assert(test2 == test1);
  assert(test2.getX() == test1.getX());
  assert(test2.getY() == test1.getY());
  std::cout << "Test successful" << std::endl;


  // update test
  std::cout << std::endl << "update() test" << std::endl;
  pe::Vector2i test3(10, 5);
  int val1 = 122;
  int val2 = 300;
  pe::Vector2i test4 = pe::Vector2i(val1, val2);
  assert(test3.getX() == 10 && test3.getY() == 5);
  test3.update(val1, val2);
  assert(test3.getX() == val1 && test3.getY() == val2);
  assert(test3 == test4);
  std::cout << "Test successful" << std::endl;


  // assignment test
  std::cout << std::endl << "Assignment test" << std::endl;
  pe::Vector2f test5(100.f, 100.f);
  pe::Vector2f test6(200.f, 200.f);
  pe::Vector2f test7;
  test7 = test5 + test6;
  assert(test7.getX() == 300.f && test7.getY() == 300.f);
  std::cout << "Test successful" << std::endl;

  // multiplication and sum test
  std::cout << std::endl << "Multiplication and sum test" << std::endl;
  pe::Vector2i test8(20, 40);
  pe::Vector2i test9 = pe::Vector2i(80, 60);
  test9 *= 100;
  assert(test9.getX() == 8000 && test9.getY() == 6000);
  test9 = test9 + test8;
  assert(test9.getX() == 8020 && test9.getY() == 6040);
  pe::Vector2i test10(10, 10);
  test9 = test9 * test10;
  assert(test9.getX() == 80200 && test9.getY() == 60400);
  assert(test10.getX() == 10 && test10.getY() == 10);
  std::cout << "Test successful" << std::endl;

  // greater than and smaller than operator tests
  std::cout << std::endl << "Greater and smaller than tests" << std::endl;
  pe::Vector2u test11(20, 40);
  pe::Vector2u test12(18, 41);
  pe::Vector2u test13(130, 45);
  assert(test13 > test11 && test13 > test12);
  assert(test12 < test13);
  assert(!(test12 < test11));
  pe::Vector2u test14(20, 10);
  assert(test11 >= test14);
  pe::Vector2u test15(3, 10);
  assert(test15 <= test14);
  pe::Vector2u test16 = test15;
  assert(test16 >= test15 && test16 <= test15);
  std::cout << "Test succesful" << std::endl;

  std::cout << "All tests passed" << std::endl;

  return 0;
}
