/**
  *   @file Shape.cpp
  *   @author Lauri Westerholm
  *   @brief Contains source code for Shape
  */


#include "../include/Shape.hpp"

namespace pe {

  // Empty constructor
  Shape::Shape() {}

  // Box shape constructor
  Shape::Shape(Vector2f left_upper, float width, float height) {
    frame.push_back(left_upper);
    frame.push_back( Vector2f(left_upper.getX() + width, left_upper.getY()) );
    frame.push_back( Vector2f(left_upper.getX() + width, left_upper.getY() + height) );
    frame.push_back( Vector2f(left_upper.getX(), left_upper.getY() + height) );
    // assign min and max vectors
    *min = frame[0];
    *max = frame[3];
    CenterMass();
  }

  //  Copy constructor
  Shape::Shape(const Shape& shape) {
    for (Vector2f item : shape.frame) {
      frame.push_back(item);
    }
    CenterMass();
  }

  // Assignment overload
  Shape& Shape::operator=(const Shape& shape) {
    frame.clear();
    for (Vector2f item : shape.frame) {
      frame.push_back(item);
    }
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

  // Check if point is inside Shape
  bool Shape::isInside(Vector2f& point) {
    // first do rough and quick check
    if (max == nullptr || min == nullptr) return false;
    if (point > *max || point < *min) return false;
    // now point can be inside or outside Shape


  }

  // Center of polygon mass
  void Shape::CenterMass() {
    float central_x = 0.f;
    float central_y = 0.f;
    float A = 0.f;
    if (frame.size() > 2) {
      float temp = 0;
      unsigned i = 0;
      for (; i < frame.size() - 1; i++) {
        temp = frame[i].getX() * frame[i + 1].getY() - frame[i + 1].getX() * frame[i].getY();
        A += temp;
        central_x += temp * (frame[i].getX() + frame[i + 1].getX());
        central_y += temp * (frame[i].getY() + frame[i + 1].getY());
      }
      // add the final values to make the polygon complete
      temp = frame[i].getX() * frame[0].getY() - frame[0].getX() * frame[i].getY();
      A += temp;
      central_x += temp * (frame[i].getX() + frame[0].getX());
      central_y += temp * (frame[i].getY() + frame[0].getY());

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
    else if (frame.size() == 2) {
      // line shape
      central_x = (frame[0].getX() + frame[1].getX()) / 2.f;
      central_y = (frame[0].getY() + frame[1].getY()) / 2.f;
    }

    mass_center = Vector2f(central_x, central_y);
  }

}// end of namespace pe
