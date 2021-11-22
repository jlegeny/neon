#include "renderer.h"

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/bitmap.h>

#include <array>
#include <cmath>
#include <iostream>

#include "util.h"

constexpr int DIALOG_FONT_SIZE = 40;
constexpr int DIALOG_PADDING = 20;
constexpr int DIALOG_MARGIN = 40;

constexpr ALLEGRO_COLOR MAGENTA = {1.0, 0.28, 0.76, 1};
constexpr ALLEGRO_COLOR CYAN = {0, 1, 1, 1};
constexpr ALLEGRO_COLOR OBSIDIAN = {0, 0, 0, 0.9};

constexpr std::pair<Texture, const char*> TEXTURE_FILES[] = {
    {Texture::CURSOR_NOTHING, "assets/cursors/cursor-nothing.png"},
    {Texture::CURSOR_LOOK, "assets/cursors/cursor-look.png"},
    {Texture::CURSOR_WALK, "assets/cursors/cursor-walk.png"},
    {Texture::BEDROOM_00_00, "assets/textures/bedroom-00-00.png"},
    {Texture::BEDROOM_00_01, "assets/textures/bedroom-00-01.png"},
    {Texture::BEDROOM_00_02, "assets/textures/bedroom-00-02.png"},
    {Texture::BEDROOM_00_03, "assets/textures/bedroom-00-03.png"},
};

Renderer::Renderer(int width, int height)
    : width_(width)
    , height_(height)
    , dialog_font(
          al_load_ttf_font("assets/ForcedSquare.ttf", DIALOG_FONT_SIZE, 0),
          al_destroy_font) {
  dialog_font_line_height = al_get_font_line_height(dialog_font.get());
}

void Renderer::init() {
  for (auto [k, v] : TEXTURE_FILES) {
    ALLEGRO_PATH* path = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
    al_join_paths(path, al_create_path(v));
    std::cout << "Loading [" << al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP)
              << "] ... ";
    auto* texture = al_load_bitmap(al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP));
    if (!texture) {
      std::cout << "ERROR" << std::endl;
      std::cerr << "Failed to load ["
                << al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP) << "] "
                << al_get_errno() << std::endl;
      exit(1);
    }
    textures_[k] = texture;
    texture_dimensions_[k] = {
        static_cast<float>(al_get_bitmap_width(texture)),
        static_cast<float>(al_get_bitmap_height(texture)),
    };
    std::cout << " OK" << std::endl;
  }
}

void Renderer::reset(int width, int height) {
  width_ = width;
  height_ = height;
}

void Renderer::draw(const Game& game, const Vec2 sMousePos) const {
  if (game.currentRoom) {
    drawRoom(**game.currentRoom);
    if (game.debug) {
      drawRegions(**game.currentRoom, game.hoverRegion);
    }
    drawPlayer(**game.currentRoom, game.player);
    drawTextBubbles(game);
    drawCursor(game, sMousePos);
  }
}

Vec2 Renderer::b2s(Vec2 point, Rect rect) const {
  return {
      (point.x - rect.x) * (width_ / rect.w),
      (point.y - rect.y) * (height_ / rect.h),
  };
}

Vec2 Renderer::s2b(Vec2 point, Rect rect) const {
  return {
      (rect.x + point.x / width_ * rect.w),
      (rect.y + point.y / height_ * rect.h),
  };
}

void Renderer::drawRoom(const Room& room) const {
  Rect rect = room.currentRect();
  Texture background = room.currentTexture();

  al_draw_scaled_bitmap(textures_.at(background), rect.x, rect.y, rect.w,
                        rect.h, 0, 0, width_, height_, 0);
  // al_draw_bitmap(textures_.at(background), 0, 0, 0);
}

void Renderer::drawCursor(const Game& game, Vec2 sMousePos) const {
  Texture cursorTexture = Texture::CURSOR_NOTHING;
  if (game.currentRoom && game.hoverRegion) {
    auto region = (*game.currentRoom)->regions_.at(*game.hoverRegion);
    if (region.type == RegionType::FLOOR) {
      cursorTexture = Texture::CURSOR_WALK;
    } else {
      cursorTexture = Texture::CURSOR_LOOK;
    }
  }
  al_draw_bitmap(textures_.at(cursorTexture), sMousePos.x, sMousePos.y, 0);
}

void Renderer::drawRegions(const Room& room,
                           std::optional<std::string> hoverRegion) const {
  Rect rect = room.currentRect();
  for (const auto& [n, r] : room.regions_) {
    auto quad = r.bitmap;
    for (int i = 0; i < 4; ++i) {
      int j = (i + 1) % 4;
      auto a = b2s(quad[i], rect);
      auto b = b2s(quad[j], rect);
      auto color = hoverRegion && n == *hoverRegion ? CYAN : MAGENTA;
      al_draw_line(a.x, a.y, b.x, b.y, color, 2.);
    }
  }
}

void Renderer::drawPlayer(const Room& room, const Player& player) const {
  int pixelSize = 7;
  for (size_t i = 0; i < player.pixelOffsets.size(); ++i) {
    Vec2 bOffset = player.pixelOffsets[i];
    Vec2 bPos = bOffset;
    if (player.frames.size()) {
      auto frame = player.frames.front();
      bPos.x = bPos.x + 1 * (frame.nextPixelOffsets[i].x - bPos.x) *
                            static_cast<float>(player.frameDt) /
                            static_cast<float>(frame.duration);
      bPos.y = bPos.y + 1 * (frame.nextPixelOffsets[i].y - bPos.y) *
                            static_cast<float>(player.frameDt) /
                            static_cast<float>(frame.duration);
    }
    Vec2 sPos = b2s(player.bPos + bPos, room.currentRect());
    int margin = (pixelSize - 1) / 2;
    al_draw_filled_rectangle(sPos.x - margin, sPos.y - margin, sPos.x + margin,
                             sPos.y + margin, CYAN);
  }
}

void Renderer::drawTextBubbles(const Game& game) const {
  if (game.player.state == PlayerState::TALKING) {
    int lastDialogHeight = 0;
    if (game.dialogs.empty()) {
      return;
    }
    const auto& rect = (*game.currentRoom)->currentRect();
    Vec2 bDialogPos{};
    for (size_t i = 0; i < game.dialogs.size(); ++i) {
      const auto& dialog = game.dialogs[i];
      if (i == 0) {
        bDialogPos = dialog.bPos;
      } else {
        if (dialog.bPos.x <= 0 || dialog.bPos.y <= 0) {
          bDialogPos.x += dialog.bPos.x;
          bDialogPos.y += dialog.bPos.y + lastDialogHeight;
        } else {
          bDialogPos = dialog.bPos;
        }
      }
      Vec2 sPos = b2s(bDialogPos, rect);

      int sWidth = 0;
      for (const std::string& line : dialog.text) {
        sWidth = std::max(sWidth,
                          al_get_text_width(dialog_font.get(), line.c_str()));
      }
      al_draw_filled_rectangle(
          sPos.x, sPos.y, sPos.x + sWidth + DIALOG_PADDING * 2,
          sPos.y + dialog.text.size() * dialog_font_line_height +
              DIALOG_PADDING * 2,
          OBSIDIAN);
      int lineIndex = 0;
      for (const std::string& line : dialog.text) {
        al_draw_text(
            dialog_font.get(), CYAN, sPos.x + DIALOG_PADDING,
            sPos.y + DIALOG_PADDING + lineIndex * dialog_font_line_height, 0,
            line.c_str());
        lineIndex++;
      }
      lastDialogHeight =
          s2b({0, static_cast<float>(lineIndex * dialog_font_line_height +
                                     2 * DIALOG_PADDING + DIALOG_MARGIN)},
              {0, 0, rect.w, rect.h})
              .y;
    }
  }
}
