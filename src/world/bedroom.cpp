#include "bedroom.h"

#include <cstdlib>

#include "../game.h"
#include "animations.h"

Bedroom::Bedroom(Game& game)
    : Room(game) {
  regions_["bed-01"] = {
      RegionType::FLOOR,
      {{
          {11, 672},
          {314, 670},
          {332, 653},
          {64, 639},
      }},
      79,
      0,
  };
  regions_["bed-02"] = {
      RegionType::FLOOR,
      {{
          {227, 646},
          {332, 653},
          {393, 597},
          {287, 597},
      }},
      79,
      0,
  };
  regions_["bed-03"] = {
      RegionType::FLOOR,
      {{
          {317, 598},
          {393, 597},
          {433, 557},
          {370, 557},
      }},
      79,
      0,
  };
  regions_["bed-04"] = {
      RegionType::FLOOR,
      {{
          {370, 557},
          {433, 557},
          {460, 531},
          {370, 528},
      }},
      79,
      0,
  };
  regions_["floor"] = {
      RegionType::FLOOR,
      {{
          {325, 829},
          {1448, 829},
          {1094, 545},
          {537, 545},
      }},
      155,
      0,
  };
  regions_["top-shelf"] = {
      RegionType::FLOOR,
      {{
          {-15, 414},
          {298, 415},
          {455, 363},
          {247, 361},
      }},
      79,
      0,
  };
  regions_["laptop-lid"] = {
      RegionType::FLOOR,
      {{
          {1160, 552},
          {1167, 552},
          {1141, 536},
          {1132, 536},
      }},
      79,
      0,
  };
  regions_["desk-01"] = {
      RegionType::FLOOR,
      {{
          {1059, 477},
          {1167, 477},
          {1070, 443},
          {1006, 442},
      }},
      79,
      0,
  };
  regions_["desk-02"] = {
      RegionType::FLOOR,
      {{
          {896, 452},
          {1034, 462},
          {1006, 442},
          {886, 440},
      }},
      79,
      0,
  };
  regions_["ladder-01"] = {
      RegionType::FLOOR,
      {{
          {474, 555},
          {487, 555},
          {497, 541},
          {488, 541},
      }},
      0,
      0,
  };
  regions_["ladder-02"] = {
      RegionType::FLOOR,
      {{
          {472, 539},
          {484, 539},
          {495, 526},
          {485, 526},
      }},
      0,
      0,
  };
  regions_["ladder-03"] = {
      RegionType::FLOOR,
      {{
          {472, 520},
          {482, 520},
          {493, 510},
          {486, 510},
      }},
      0,
      0,
  };
  regions_["ladder-04"] = {
      RegionType::FLOOR,
      {{
          {470, 500},
          {480, 500},
          {494, 490},
          {485, 490},
      }},
      0,
      0,
  };
  regions_["ladder-05"] = {
      RegionType::FLOOR,
      {{
          {470, 482},
          {480, 482},
          {494, 471},
          {484, 471},
      }},
      0,
      0,
  };
  regions_["ladder-06"] = {
      RegionType::FLOOR,
      {{
          {469, 462},
          {479, 462},
          {492, 453},
          {483, 453},
      }},
      0,
      0,
  };
  regions_["ladder-07"] = {
      RegionType::FLOOR,
      {{
          {469, 443},
          {479, 443},
          {491, 436},
          {482, 436},
      }},
      0,
      0,
  };
  regions_["ladder-08"] = {
      RegionType::FLOOR,
      {{
          {469, 422},
          {480, 422},
          {489, 417},
          {482, 417},
      }},
      0,
      0,
  };
  regions_["ladder-09"] = {
      RegionType::FLOOR,
      {{
          {468, 404},
          {479, 404},
          {490, 398},
          {482, 398},
      }},
      0,
      0,
  };
  regions_["ladder-10"] = {
      RegionType::FLOOR,
      {{
          {469, 383},
          {478, 383},
          {489, 378},
          {480, 379},
      }},
      0,
      0,
  };
  regions_["ladder-11"] = {
      RegionType::FLOOR,
      {{
          {469, 365},
          {478, 365},
          {489, 360},
          {480, 360},
      }},
      0,
      0,
  };
  regions_["ladder-12"] = {
      RegionType::FLOOR,
      {{
          {466, 344},
          {475, 344},
          {485, 340},
          {480, 340},
      }},
      0,
      0,
  };
  /*
  regions_["ladder-14"] = {
      RegionType::FLOOR,
      {{
          {474, 555},
          {487, 555},
          {497, 541},
          {488, 541},
      }},
      0,
      0,
  };*/

  regions_["main-screen"] = {
      RegionType::OBJECT,
      {{
          {929, 419},
          {1091, 439},
          {1103, 314},
          {932, 311},
      }},
      0,
      0,
  };
  regions_["laptop"] = {
      RegionType::OBJECT,
      {{
          {1082, 591},
          {1159, 611},
          {1167, 562},
          {1134, 545},
      }},
      0,
      0,
  };
  regions_["sleeper"] = {
      RegionType::OBJECT,
      {{
          {116, 622},
          {218, 635},
          {365, 538},
          {322, 500},
      }},
      0,
      0,
  };

  addTinyTransition("ladder-01", "ladder-02");
  addTinyTransition("ladder-02", "ladder-03");
  addTinyTransition("ladder-03", "ladder-04");
  addTinyTransition("ladder-04", "ladder-05");
  addTinyTransition("ladder-05", "ladder-06");
  addTinyTransition("ladder-06", "ladder-07");
  addTinyTransition("ladder-07", "ladder-08");
  addTinyTransition("ladder-08", "ladder-09");
  addTinyTransition("ladder-09", "ladder-10");
  addTinyTransition("ladder-10", "ladder-11");
  addTinyTransition("ladder-11", "ladder-12");
  //  addTinyTransition("ladder-12", "ladder-13");
  addTransition("floor", "ladder-01", {515, 588}, {487, 548}, true);
  addTransition("floor", "laptop-lid", {1164, 607}, {1161, 550}, true);
  addTransition("laptop-lid", "desk-01", {1140, 539}, {1135, 475}, true);
  addTransition("desk-01", "desk-02", {1024, 452}, {1015, 451}, true);
  addTransition("bed-01", "bed-02", {276, 652}, {281, 646}, true);
  addTransition("bed-02", "bed-03", {351, 600}, {355, 593}, true);
  addTransition("bed-03", "bed-04", {397, 559}, {397, 554}, true);
  addTransition("bed-04", "ladder-02", {456, 541}, {481, 534}, true);
  addTransition("top-shelf", "ladder-11", {443, 364}, {472, 363}, true);
}

Rect Bedroom::currentRect() const {
  float pan = 100;
  float top = 120;
  float bottom = 820;
  float width = ((bottom - top) / 920.) * 1480;
  return {pan, top, width, bottom - top};
}

Texture Bedroom::currentTexture() const {
  switch (frame_) {
    case 0:
      return Texture::BEDROOM_00_00;
    case 1:
      return Texture::BEDROOM_00_01;
    case 2:
      return Texture::BEDROOM_00_02;
    case 3:
      return Texture::BEDROOM_00_03;
    default:
      exit(1);
  }
}

void Bedroom::update(Player& player, int dt) {
  time_ += dt;
  if (time_ > last_udpdate_ + 128) {
    frame_ = (frame_ + 1) % 4;
    last_udpdate_ = time_;
  }

  if (player.animation == PlayerAnimation::NONE) {
    if (player.state == PlayerState::SLEEPING) {
      player.state = PlayerState::WAKING_UP;
      Animations::wakeUp(player);
    } else if (player.state == PlayerState::WALKING) {
      Animations::snake(player);
    } else if (player.state == PlayerState::IDLE) {
      Animations::idle(player);
    }
  }
}

void Bedroom::animationFinished(Player& player) {
  if (player.animation == PlayerAnimation::WAKING_UP) {
    if (player.state == PlayerState::WAKING_UP) {
      player.state = PlayerState::IDLE;
      player.animation = PlayerAnimation::NONE;
    }
  } else if (player.animation == PlayerAnimation::SNAKE) {
    if (player.state == PlayerState::WALKING) {
      Animations::snake(player);
    } else {
      player.state = PlayerState::WAKING_UP;
      Animations::wakeUp(player);
    }
  } else if (player.animation == PlayerAnimation::IDLE) {
    Animations::idle(player);
  }
}

void Bedroom::lookAt(const std::string& regionId) {
  if (regionId == "main-screen") {
    this->dialog("main-screen-describe-1");
  } else if (regionId == "laptop") {
    this->dialog("laptop-describe-1");
  } else if (regionId == "sleeper") {
    this->dialog("sleeper-describe-1");
  }
}

void Bedroom::dialog(const std::string& dialogId) {
  if (dialogId == "main-screen-describe-1") {
    game_.player.state = PlayerState::TALKING;
    game_.textBubble(R"(
Computer Screen
---

The most interesting object in this room...

)",
                     Vec2{763, 266}, "main-screen-describe-2-nothing");
  } else if (dialogId == "main-screen-describe-2-nothing") {
    game_.textBubble("It's currently not displaying anything interesting",
                     Vec2{0, 0}, std::nullopt);
  } else if (dialogId == "laptop-describe-1") {
    game_.player.state = PlayerState::TALKING;
    game_.textBubble(R"(
Precariously Positioned Laptop
---

It mentions something about a firewall status.

Would be a shame if somebody stepped on it.

)",
                     Vec2{776, 352}, "laptop-describe-2");
  } else if (dialogId == "laptop-describe-2") {
    game_.textBubble("Does that look like a footprint?", Vec2{0, 0},
                     "laptop-describe-3");
  } else if (dialogId == "laptop-describe-3") {
    game_.textBubble(R"(
In any case all those flashing red labels
mentioning ERROR can't be good!
)",
                     Vec2{0, 0}, "laptop-describe-4");
  } else if (dialogId == "laptop-describe-4") {
    game_.textBubble("Also, somebody should plug it in!", Vec2{0, 0},
                     std::nullopt);
  } else if (dialogId == "sleeper-describe-1") {
    game_.player.state = PlayerState::TALKING;
    game_.textBubble(R"(
A Snoring NetRunner
---

It's sad when your job depends one somebody
else entirely.
)",
                     Vec2{120, 180}, "sleeper-describe-2");
  } else if (dialogId == "sleeper-describe-2") {
    game_.textBubble("I rang, they didn't wake up.", Vec2{0, 0},
                     "sleeper-describe-3");
  } else if (dialogId == "sleeper-describe-3") {
    game_.textBubble(
        R"(
Now that I think about it, they did mention
some super important job before passing out
drunk.
)",
        Vec2{0, 0}, "sleeper-describe-4");
  } else if (dialogId == "sleeper-describe-4") {
    game_.textBubble("I need to find a way to rouse them up.", Vec2{0, 0},
                     std::nullopt);
  }
}

void Bedroom::playerEnter(Player& player) const {
  player.state = PlayerState::SLEEPING;
  player.bPos.x = 405;
  player.bPos.y = 537;
  player.vZ = *zAt(player.bPos);
}
