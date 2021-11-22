#ifndef DATA_H
#define DATA_H

#include <deque>
#include <vector>

constexpr float WALK_SPEED = 0.5;

enum class Texture {
  CURSOR_NOTHING,
  CURSOR_LOOK,
  CURSOR_WALK,
  BEDROOM_00_00,
  BEDROOM_00_01,
  BEDROOM_00_02,
  BEDROOM_00_03,
};

struct Rect {
  float x, y;
  float w, h;
};

enum class PlayerState {
  SLEEPING,
  WAKING_UP,
  IDLE,
  WALKING,
  TALKING,
};

enum class PlayerAnimation {
  NONE,
  WAKING_UP,
  IDLE,
  SNAKE,
};

struct Vec2 {
  float x, y;
};

struct Vec3 {
  float x, y, z;
};

struct Quad {
  Vec3 a, b, c, d;
};

struct AnimationFrame {
  std::vector<Vec2> nextPixelOffsets;
  int duration;
};

struct Player {
  PlayerState state;
  PlayerAnimation animation;
  std::deque<Vec2> bWaypoints;
  Vec2 bPos;
  Vec2 bDest;
  float vZ;
  std::vector<Vec2> pixelOffsets;
  std::deque<AnimationFrame> frames;
  int frameDt;
};

#endif  // DATA_H
