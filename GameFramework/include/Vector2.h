#pragma once

struct Vector2
{
  Vector2() = default;
  Vector2(float x, float y) : x(x), y(y) {}
  float x = 0.0f;
  float y = 0.0f;

  Vector2 operator-(const Vector2& other) const {
    return {x - other.x, y - other.y};
  }
};