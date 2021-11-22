#include "game.h"

#include <iostream>

#include "util.h"

Game::Game()
    : currentRoom(std::nullopt)
    , player({})
    , time_(0) {
  player.pixelOffsets = {
      {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
      {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0},
  };
}

void Game::update(uint32_t dt) {
  if (state != GameState::MAIN_LOOP) {
    return;
  }
  if (currentRoom) {
    (*currentRoom)->update(player, dt);
  }
  if (player.state == PlayerState::WALKING) {
    Vec2 d = {player.bDest.x - player.bPos.x, player.bDest.y - player.bPos.y};
    float norm = sqrt(d.x * d.x + d.y * d.y);
    Vec2 nd = {d.x / norm, d.y / norm};
    if (norm > WALK_SPEED * dt) {
      player.bPos.x += nd.x * WALK_SPEED * dt;
      player.bPos.y += nd.y * WALK_SPEED * dt;
    } else {
      if (player.bWaypoints.size()) {
        player.bDest = player.bWaypoints.front();
        player.bWaypoints.pop_front();
      } else {
        player.bPos.x = player.bDest.x;
        player.bPos.y = player.bDest.y;
        player.state = PlayerState::IDLE;
      }
    }
  }
  if (!player.frames.empty()) {
    AnimationFrame& frame = player.frames.front();

    player.frameDt += dt;
    /*
    for (size_t i = 0; i < player.pixelOffsets.size(); ++i) {
      Vec2& bPos = player.pixelOffsets[i];
      Vec2& bDest = frame.nextPixelOffsets[i];
      bPos.x = bPos.x + (bDest.x - bPos.x) +
               0 * static_cast<float>(player.frameDt) /
                   static_cast<float>(frame.duration);
      bPos.y = bPos.y + (bDest.y - bPos.y) +
               0 * static_cast<float>(player.frameDt) /
                   static_cast<float>(frame.duration);
    }
    */
    if (player.frameDt >= frame.duration) {
      player.pixelOffsets = player.frames.front().nextPixelOffsets;
      player.frames.pop_front();
      player.frameDt = 0;
      if (player.frames.empty()) {
        (*currentRoom)->animationFinished(player);
      }
    }
  }
}

void Game::addRoom(std::string name, Room* room) {
  rooms_.emplace(std::make_pair(name, room));
}

void Game::setRoom(std::string name) {
  auto room = rooms_.find(name);
  if (room == rooms_.end()) {
    return;
  }
  currentRoom = room->second.get();
  (*currentRoom)->playerEnter(player);
}

void Game::primaryAction(Vec2 bAt) {
  if (player.state == PlayerState::SLEEPING) {
    return;
  }
  if (player.state == PlayerState::TALKING) {
    return nextDialog();
  }
  if (!hoverRegion) {
    return;
  }
  const auto& region = (*currentRoom)->regions_.at(*hoverRegion);
  if (region.type == RegionType::FLOOR) {
    goTo(bAt);
  } else if (region.type == RegionType::OBJECT) {
    lookAt(*hoverRegion);
  }
}

void Game::textBubble(std::string text, Vec2 bPos,
                      std::optional<std::string> nextDialogId) {
  std::vector<std::string> lines;

  auto start = 0U;
  auto end = text.find('\n');
  if (end == std::string::npos) {
    lines = {text};
  }
  while (end != std::string::npos) {
    std::string line = text.substr(start, end - start);
    if (!(lines.empty() && line.empty())) {
      lines.push_back(line);
    }
    start = end + 1;
    end = text.find('\n', start);
  }

  dialogs.push_back({lines, bPos});
  this->nextDialogId = nextDialogId;
}

void Game::clearText() {
  dialogs.clear();
}

void Game::goTo(Vec2 bDest) {
  auto path = (*currentRoom)->findPath(player.bPos, bDest);
  if (path && path->size()) {
    player.state = PlayerState::WALKING;
    player.frames.clear();
    player.animation = PlayerAnimation::NONE;
    player.bWaypoints.assign(path->begin(), path->end());
    player.bDest = player.bWaypoints.front();
    player.bWaypoints.pop_front();
  } else {
    if (player.state == PlayerState::WALKING) {
      player.bWaypoints.clear();
    }
  }
}

void Game::lookAt(std::string regionId) {
  (*currentRoom)->lookAt(regionId);
}

void Game::nextDialog() {
  if (nextDialogId) {
    (*currentRoom)->dialog(*nextDialogId);
  } else {
    clearText();
    player.state = PlayerState::IDLE;
  }
}
