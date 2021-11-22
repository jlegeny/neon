#ifndef UTIL_H
#define UTIL_H

#include "data.h"

float sqdist(float ax, float ay, float bx, float by);
float dist(Vec2 a, Vec2 b);
Vec2 operator+(const Vec2& lhs, const Vec2& rhs);
Vec2 operator-(const Vec2& lhs, const Vec2& rhs);
Vec2 operator/(const Vec2& lhs, const float rhs);
bool operator==(const Vec2& lhs, const Vec2& rhs);

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

#endif  // UTIL_H
