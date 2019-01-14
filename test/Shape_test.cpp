/**
  *   @file Shape_test.cpp
  *   @author Lauri Westerholm
  *   @brief Contains test main for Shape
  */

#include "../include/Shape.hpp"
#include <iostream>
#include <cassert>

/**
  *   @brief Test main for Shape
  */

int main() {

  std::cout << "Shape constructor test" << std::endl;
  pe::Shape shape;
  assert(shape.getCenter() == pe::Vector2f(0.f, 0.f));
  shape = pe::Shape(10.f, 10.f);
  pe::Vector2f center = shape.getCenter();
  std::cout << "Center: " << center;
  assert(center == pe::Vector2f(5.f, 5.f));
  pe::Shape shape2 = shape;
  assert(shape2.getCenter() == shape.getCenter());
  std::cout << "Test succesful" << std::endl;

  std::cout << std::endl << "getFrame test" << std::endl;
  std::deque<pe::Vector2f> frame = shape2.getFrame();
  for (auto item : frame) {
    std::cout << item;
  }
  std::cout << "Test succesful" << std::endl;

  std::cout << std::endl << "getMin and getMax test" << std::endl;
  pe::Shape test1;
  assert(test1.getMin() == pe::Vector2f(0.f, 0.f));
  assert(test1.getMax() == pe::Vector2f(0.f, 0.f));
  test1 = pe::Shape(30.f, 25.f);
  assert(test1.getMin() == pe::Vector2f(0.f, 0.f));
  assert(test1.getMax() == pe::Vector2f(30.f, 25.f));
  pe::Shape test2 = pe::Shape(100.f, -100.f); // should take abs from negative values
  assert(test2.getMin() == pe::Vector2f(0.f, 0.f));
  frame = test2.getFrame();
  for (auto item : frame) {
    std::cout << item;
  }
  assert(test2.getMax() == pe::Vector2f(100.f, 100.f));
  std::cout << "Test succesful" << std::endl;

  std::cout << std::endl << "getArea test" << std::endl;
  pe::Shape test3;
  assert(test3.getArea() == 0.f);
  pe::Shape test4(30.f, 10.f);
  assert(test4.getArea() == 300.f);
  std::cout << "Test succesful" << std::endl;

  std::cout << std::endl << "All test succesfully completed" << std::endl;

  return 0;
}
