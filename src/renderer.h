#ifndef RENDERER_H
#define RENDERER_H

#include <allegro5/allegro_font.h>
#include <allegro5/bitmap.h>

#include <array>
#include <cstdint>
#include <map>
#include <random>

#include "game.h"
#include "room.h"

struct Pixel {
  int16_t x, y;
};

class Renderer {
 public:
  Renderer(int width, int height);
  void init();
  void reset(int width, int height);

  void draw(const Game& game, const Vec2 sMousePos) const;

  Vec2 s2b(Vec2 point, Rect rect) const;
  Vec2 b2s(Vec2 point, Rect rect) const;

 private:
  void drawRoom(const Room& room) const;
  void drawRegions(const Room& room,
                   std::optional<std::string> hoverRegion) const;
  void drawPlayer(const Room& room, const Player& player) const;
  void drawTextBubbles(const Game& game) const;
  void drawCursor(const Game& game, Vec2 sMousePos) const;

 private:
  int width_;
  int height_;

  std::default_random_engine random_generator_;
  std::map<Texture, ALLEGRO_BITMAP*> textures_;
  std::map<Texture, Vec2> texture_dimensions_;
  std::unique_ptr<ALLEGRO_FONT, void (*)(ALLEGRO_FONT*)> dialog_font;
  int dialog_font_line_height;
};

#endif  // RENDERER_H
