#include "util.h"

#include <cmath>

float sqdist(float ax, float ay, float bx, float by) {
  return (ax - bx) * (ax - bx) + (ay - by) * (ay - by);
}

float dist(Vec2 a, Vec2 b) {
  return std::sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Vec2 operator+(const Vec2& lhs, const Vec2& rhs) {
  return {lhs.x + rhs.x, lhs.y + rhs.y};
}

Vec2 operator-(const Vec2& lhs, const Vec2& rhs) {
  return {lhs.x - rhs.x, lhs.y - rhs.y};
}

Vec2 operator/(const Vec2& lhs, const float rhs) {
  return {lhs.x / rhs, lhs.y / rhs};
}

bool operator==(const Vec2& lhs, const Vec2& rhs) {
  return lhs.x == rhs.x && lhs.y == rhs.y;
}
