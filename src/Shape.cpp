/**
  *   @file Shape.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source code for Shape
  */


#include "../include/Shape.hpp"

namespace pe {

  // Empty constructor
  Shape::Shape(): area(0.f) {}

  // Box shape constructor
  Shape::Shape(float width, float height) {
    width = std::abs(width);
    height = std::abs(height);
    frame.push_back( Vector2f(0.f, 0.f) );
    frame.push_back( Vector2f(width, 0.f) );
    frame.push_back( Vector2f(width, height) );
    frame.push_back( Vector2f(0.f, height) );
    frame.push_back( Vector2f(0.f, 0.f) ); // now the box is closed
    // assign min and max vectors
    min = &frame[0];
    max = &frame[2];
    CenterMass();
  }

  //  Copy constructor
  Shape::Shape(const Shape& shape) {
    for (Vector2f item : shape.frame) {
      frame.push_back(item);
    }
    FindMinMax();
    CenterMass();
  }

  // Assignment overload
  Shape& Shape::operator=(const Shape& shape) {
    frame.clear();
    for (Vector2f item : shape.frame) {
      frame.push_back(item);
    }
    FindMinMax();
    CenterMass();
    return *this;
  }

  // Get mass_center
  Vector2f& Shape::getCenter() {
    return mass_center;
  }

  // Get frame
  const std::deque<Vector2f>& Shape::getFrame() {
    return frame;
  }

  // Get min
  Vector2f Shape::getMin() {
    Vector2f vect;
    if (min != nullptr) {
      vect = *min;
    }
    return vect;
  }

  // Get max
  Vector2f Shape::getMax() {
    Vector2f vect;
    if (max != nullptr) {
      vect = *max;
    }
    return vect;
  }

  // Get area
  float Shape::getArea() {
    return area;
  }

  void Shape::FindMinMax() {
    min = nullptr;
    max = nullptr;
    if (frame.size()) {
      min = &frame[0];
      max = &frame[0];

      for (unsigned i = 1; i < frame.size(); i++) {
        if (frame[i] <= *min) min = &frame[i];
        if (frame[i] >= *max) max = &frame[i];
      }
    }
  }

  // Center of polygon mass
  void Shape::CenterMass() {
    float central_x = 0.f;
    float central_y = 0.f;
    float A = 0.f;
    if (frame.size() > 3) {
      float temp = 0;
      unsigned i = 0;
      for (; i < frame.size() - 1; i++) {
        temp = frame[i].getX() * frame[i + 1].getY() - frame[i + 1].getX() * frame[i].getY();
        A += temp;
        central_x += temp * (frame[i].getX() + frame[i + 1].getX());
        central_y += temp * (frame[i].getY() + frame[i + 1].getY());
      }

      A *= 0.5;
      // use area to determine correct center of mass
      if (A) {
        central_x = central_x / (6 * A);
        central_y = central_y / (6 * A);
      }
      else {
        // smt weird happened
        central_x = 0.f;
        central_y = 0.f;
      }

    }
    else if (frame.size() == 3) {
      // line shape
      central_x = (frame[0].getX() + frame[1].getX()) / 2.f;
      central_y = (frame[0].getY() + frame[1].getY()) / 2.f;
    }

    // also update area
    area = A;
    mass_center = Vector2f(central_x, central_y);
  }

}// end of namespace pe
