#include "animations.h"

#include "../util.h"

constexpr float PIXEL_SIZE = 2;
constexpr float PIXEL_MARGIN = PIXEL_SIZE + 2;

namespace Animations {

namespace {
std::vector<Vec2> defaultOffsets() {
  static const std::vector<Vec2> offsets = {
      {PIXEL_MARGIN * -2, PIXEL_MARGIN * -4},
      {PIXEL_MARGIN * -1, PIXEL_MARGIN * -5},
      {0, PIXEL_MARGIN * -5},
      {PIXEL_MARGIN * 1, PIXEL_MARGIN * -4},
      {PIXEL_MARGIN * 1, PIXEL_MARGIN * -3},
      {0, PIXEL_MARGIN * -2},
      {PIXEL_MARGIN * -1, PIXEL_MARGIN * -2},
      {PIXEL_MARGIN * -2, PIXEL_MARGIN * -1},
      {PIXEL_MARGIN * -2, 0},
      {PIXEL_MARGIN * -1, 0},
      {0, 0},
      {PIXEL_MARGIN * 1, 0}};
  return offsets;
}
}  // namespace
void wakeUp(Player& player) {
  player.frames.clear();
  player.frames = {AnimationFrame{defaultOffsets(), 250}};
  player.animation = PlayerAnimation::WAKING_UP;
}
void idle(Player& player) {
  AnimationFrame frameA;
  frameA.nextPixelOffsets = defaultOffsets();
  frameA.duration = 500;
  for (size_t i = 0; i < 7; ++i) {
    frameA.nextPixelOffsets[i] = frameA.nextPixelOffsets[i] +
                                 Vec2{0., (7 - static_cast<float>(i)) * 0.4f};
  }
  frameA.nextPixelOffsets[11] = frameA.nextPixelOffsets[11] + Vec2{0, 0.5};

  AnimationFrame frameB;
  frameB.duration = 500;
  frameB.nextPixelOffsets = defaultOffsets();

  player.frames.push_back(frameA);
  player.frames.push_back(frameB);
  player.animation = PlayerAnimation::IDLE;
}
void snake(Player& player) {
  AnimationFrame frameA;
  frameA.nextPixelOffsets = defaultOffsets();
  frameA.duration = 100;
  frameA.nextPixelOffsets[8] =
      frameA.nextPixelOffsets[8] + Vec2{0, PIXEL_MARGIN * 1};
  frameA.nextPixelOffsets[9] = frameA.nextPixelOffsets[9] + Vec2{0, 0};
  frameA.nextPixelOffsets[10] =
      frameA.nextPixelOffsets[10] + Vec2{0, PIXEL_MARGIN * 1};
  frameA.nextPixelOffsets[11] = frameA.nextPixelOffsets[11] + Vec2{0, 0};

  AnimationFrame frameB;
  frameB.nextPixelOffsets = defaultOffsets();
  frameB.duration = 100;
  frameB.nextPixelOffsets[8] = frameB.nextPixelOffsets[8] + Vec2{0, 0};
  frameB.nextPixelOffsets[9] =
      frameB.nextPixelOffsets[9] + Vec2{0, PIXEL_MARGIN * 1};
  frameB.nextPixelOffsets[10] = frameB.nextPixelOffsets[10] + Vec2{0, 0};
  frameB.nextPixelOffsets[11] =
      frameB.nextPixelOffsets[11] + Vec2{0, PIXEL_MARGIN * 1};

  player.frames.push_back(frameA);
  player.frames.push_back(frameB);
  player.animation = PlayerAnimation::SNAKE;
}
}  // namespace Animations
