#include <valarray>
#ifndef PINGPONG_SDL2_VECTOR2_HPP

class Vector2 {
 public:
  float x, y;

  explicit Vector2(float x = 0.0f, float y = 0.0f) : x{x}, y{y} {}

  Vector2 operator+(const Vector2& other) const {
    return Vector2(x + other.x, y + other.y);
  }

  Vector2 operator-(const Vector2& other) const {
    return Vector2(x - other.x, y - other.y);
  }

  Vector2 operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
  }

  Vector2 operator/(float scalar) const {
    if (scalar != 0.0f) {
      return Vector2(x / scalar, y / scalar);
    } else {
      return Vector2(0.0f, 0.0f);
    }
  }

  bool operator==(const Vector2& other) const {
    return x == other.x && y == other.y;
  }

  bool operator!=(const Vector2& other) const { return !(*this == other); }

  Vector2& operator+=(Vector2 const& other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  static Vector2 normalize(Vector2 vec) {
    float length = std::sqrt(vec.x * vec.x + vec.y * vec.y);
    if (length != 0) {
      vec.x /= length;
      vec.y /= length;
    }
    return vec;
  }
};

#define PINGPONG_SDL2_VECTOR2_HPP

#endif  // PINGPONG_SDL2_VECTOR2_HPP
