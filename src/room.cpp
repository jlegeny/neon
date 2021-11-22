#include "room.h"

#include <iostream>
#include <unordered_set>

#include "util.h"

bool inPoly(Vec2 pos, const std::array<Vec2, 4>& quad) {
  for (int i = 0; i < 4; ++i) {
    int j = (i + 1) % 4;
    auto a = quad[i];
    auto b = quad[j];
    auto det = (b.x - a.x) * (pos.y - a.y) - (b.y - a.y) * (pos.x - a.x);
    if (det >= 0) {
      return false;
    }
  }
  return true;
}

std::optional<std::string> Room::regionAt(Vec2 bPos) const {
  for (const auto& [id, region] : regions_) {
    if (inPoly(bPos, region.bitmap)) {
      return id;
    }
  }
  return std::nullopt;
}

std::optional<float> Room::zAt(Vec2 bPos) const {
  const auto regionId = regionAt(bPos);
  if (!regionId) {
    return std::nullopt;
  }
  const auto& region = regions_.at(*regionId);

  // Assume the plane is always perpendicular to the screen

  float yFront = region.bitmap[0].y;
  float yBack = region.bitmap[0].y;
  for (size_t i = 1; i < region.bitmap.size(); ++i) {
    yFront = std::max(yFront, region.bitmap[i].y);
    yBack = std::min(yBack, region.bitmap[i].y);
  }
  float t =
      (bPos.y - region.bitmap[0].y) / (region.bitmap[0].y - region.bitmap[2].y);
  return (region.zFront - region.zBack) * t;
}

std::optional<std::vector<Vec2>> Room::findPath(Vec2 bFrom, Vec2 bTo) {
  auto maybeFromRegion = regionAt(bFrom);
  auto maybeToRegion = regionAt(bTo);
  if (!maybeFromRegion || !maybeToRegion) {
    return std::nullopt;
  }

  std::string fromRegion = *maybeFromRegion;
  std::string toRegion = *maybeToRegion;

  if (fromRegion == toRegion) {
    return std::vector{bTo};
  }

  std::unordered_set<std::string> visited;
  std::unordered_set<std::string> toVisit;
  std::map<std::string, float> shortestDistanceTo;
  std::map<std::string, std::vector<Vec2>> shortestPathTo;
  std::map<std::string, Vec2> startpointIn;
  shortestDistanceTo[fromRegion] = 0;
  shortestPathTo[fromRegion] = {};
  startpointIn[fromRegion] = bFrom;
  toVisit.insert(fromRegion);
  while (!toVisit.empty()) {
    std::string regionId = *toVisit.begin();
    visited.insert(regionId);
    toVisit.erase(regionId);
    if (!transitions_.count(regionId)) {
      continue;
    }
    for (auto& [destId, dest] : transitions_.at(regionId)) {
      if (visited.contains(destId)) {
        continue;
      }
      toVisit.insert(destId);
      auto shortestDistanceToDest = shortestDistanceTo.find(destId);
      float distanceFromHere = shortestDistanceTo[regionId] +
                               dist(startpointIn.at(regionId), dest.bFrom) +
                               dist(dest.bFrom, dest.bTo);

      if (shortestDistanceToDest == shortestDistanceTo.end() ||
          shortestDistanceToDest->second > distanceFromHere) {
        shortestDistanceTo[destId] = distanceFromHere;
        startpointIn[destId] = dest.bTo;
        shortestPathTo[destId] = shortestPathTo.at(regionId);
        shortestPathTo[destId].push_back(dest.bFrom);
        shortestPathTo[destId].push_back(dest.bTo);
      }
    }
  }

  if (shortestPathTo.count(toRegion)) {
    shortestPathTo[toRegion].push_back(bTo);
    return shortestPathTo.at(toRegion);
  }

  return std::nullopt;
}

void Room::addTransition(std::string fromId, std::string toId, Vec2 bFrom,
                         Vec2 bTo, bool biDirectional) {
  transitions_[fromId][toId] = {
      bFrom,
      bTo,
  };
  if (biDirectional) {
    transitions_[toId][fromId] = {
        bTo,
        bFrom,
    };
  }
}

void Room::addTinyTransition(std::string fromId, std::string toId) {
  auto fromRegion = regions_.at(fromId);
  auto toRegion = regions_.at(toId);
  Vec2 fromCenter = {};
  Vec2 toCenter = {};

  for (size_t i = 0; i < fromRegion.bitmap.size(); ++i) {
    fromCenter.x += fromRegion.bitmap[i].x;
    fromCenter.y += fromRegion.bitmap[i].y;
  }
  fromCenter.x /= fromRegion.bitmap.size();
  fromCenter.y /= fromRegion.bitmap.size();
  for (size_t i = 0; i < toRegion.bitmap.size(); ++i) {
    toCenter.x += toRegion.bitmap[i].x;
    toCenter.y += toRegion.bitmap[i].y;
  }
  toCenter.x /= toRegion.bitmap.size();
  toCenter.y /= toRegion.bitmap.size();
  addTransition(fromId, toId, fromCenter, toCenter, true);
}
