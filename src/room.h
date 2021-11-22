#ifndef ROOM_H
#define ROOM_H

#include <array>
#include <map>
#include <string>
#include <vector>

#include "data.h"

enum class RegionType {
  FLOOR,
  OBJECT,
};

struct Region {
  RegionType type;
  std::array<Vec2, 4> bitmap;
  float zBack;
  float zFront;
};

struct Transition {
  Vec2 bFrom;
  Vec2 bTo;
};

class Game;

class Room
{
 public:
  virtual ~Room(){};
  virtual Texture currentTexture() const = 0;
  virtual Rect currentRect() const = 0;
  virtual void playerEnter(Player& player) const = 0;
  virtual void lookAt(const std::string& regionId) = 0;
  virtual void dialog(const std::string& dialogId) = 0;

  virtual void update(Player& player, int dt) = 0;
  virtual void animationFinished(Player& player) = 0;

  std::optional<std::string> regionAt(Vec2 bPos) const;
  std::optional<float> zAt(Vec2 bPos) const;
  std::optional<std::vector<Vec2>> findPath(Vec2 bFrom, Vec2 bTo);

 public:
  std::map<std::string, Region> regions_;
  std::map<std::string, std::map<std::string, Transition>> transitions_;

 protected:
  Room(Game& game)
      : game_(game){};

  void addTransition(std::string fromId, std::string toId, Vec2 bFrom, Vec2 bTo,
                     bool biDirectional);
  void addTinyTransition(std::string fromId, std::string toId);

  int frame_ = 0;
  int time_ = 0;
  int last_udpdate_ = 0;

  Game& game_;
};

#endif // ROOM_H
