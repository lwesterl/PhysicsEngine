/**
  *   @file Rect_test.cpp
  *   @author Lauri Westerholm
  *   @brief Test main for class Rect
  */

#include "../utils/Rect.hpp"
#include "../utils/Vector2.hpp"
#include <iostream>
#include <cassert>

/**
  *   @brief Test main for Rect"
  */

int main() {

  std::cout << "Rect Test" << std::endl;
  std::cout << "Constructor test" << std::endl;
  pe::Rectf rect1;


  assert(rect1.getPosition() == pe::Vector2f(0.f, 0.f));
  assert(rect1.getWidth() == 0.f);
  assert(rect1.getHeight() == 0.f);
  rect1 = pe::Rectf(pe::Vector2f(10.f, 100.f), 20.f, 20.f);
  assert(rect1.getWidth() == 20.f);
  pe::Rectf rect2 = rect1;
  assert(rect2.getHeight() == 20.f && rect2.getPosition() == pe::Vector2f(10.f, 100.f));
  pe::Recti rect3 = pe::Recti();
  assert(rect3.getPosition() == pe::Vector2i(0, 0));
  std::cout << "Test successful" << std::endl;

  std::cout << std::endl << "Print test" << std::endl;
  std::cout << rect1;
  std::cout << rect3;
  std::cout << "Test successful" << std::endl;

  std::cout << std::endl << "Set and get test" << std::endl;
  rect3.setWidth(100);
  assert(rect3.getWidth() == 100);
  rect3.setHeight(500);
  assert(rect3.getHeight() == 500);
  rect3.setPosition(pe::Vector2i(-100, 400));
  assert(rect3.getPosition() == pe::Vector2i(-100, 400));
  std::cout << "Test successful" << std::endl;

  std::cout << std::endl << "contains test" << std::endl;
  pe::Rectu rect4(pe::Vector2u(200, 100), 10, 10);
  assert(rect4.contains(200, 100));
  assert(rect4.contains(205, 105));
  assert(rect4.contains(pe::Vector2u(207, 105)));
  assert(!rect4.contains(pe::Vector2u(211, 105)));
  assert(!rect4.contains(202, 99));
  std::cout << "Test successful" << std::endl;

  std::cout << std::endl << "All Rect tests passed" << std::endl;
  return 0;
}
