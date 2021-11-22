#ifndef GAME_H
#define GAME_H

#include <optional>
#include <random>
#include <unordered_set>
#include <vector>

#include "room.h"

enum class GameState {
  MENU,
  MAIN_LOOP,
  QUIT,
};

struct DialogBox {
  std::vector<std::string> text;
  Vec2 bPos;
};

class Game {
 public:
  Game();

  void update(uint32_t dt);
  void addRoom(std::string name, Room* room);
  void setRoom(std::string name);

  void primaryAction(Vec2 bAt);

  void textBubble(std::string text, Vec2 bPos,
                  std::optional<std::string> nextDialogId);
  void clearText();

 public:
  std::optional<Room*> currentRoom;
  GameState state = GameState::MENU;
  bool gameover = false;
  bool debug = false;

  std::optional<std::string> hoverRegion;

  std::vector<DialogBox> dialogs;
  std::optional<std::string> nextDialogId;

  Player player;

 private:
  void goTo(Vec2 bDest);
  void lookAt(std::string regionId);
  void nextDialog();

 private:
  uint32_t time_;
  std::map<std::string, std::unique_ptr<Room>> rooms_;

  std::default_random_engine generator_;
};

#endif  // GAME_H
