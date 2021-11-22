#ifndef BEDROOM_H
#define BEDROOM_H

#include <array>
#include <map>
#include <string>

#include "../data.h"
#include "../room.h"

class Bedroom : public Room {
 public:
  Bedroom(Game& game);
  Texture currentTexture() const override;
  Rect currentRect() const override;
  void playerEnter(Player& player) const override;
  void update(Player& player, int dt) override;
  void animationFinished(Player& player) override;
  void lookAt(const std::string& regionId) override;
  void dialog(const std::string& dialogId) override;
};

#endif  // ROOM_H
