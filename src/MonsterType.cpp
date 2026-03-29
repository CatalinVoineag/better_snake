#include "MonsterType.h"
#include <SDL3/SDL.h>
#include <string>
#include <vector>
#include "Entity.h"
#include "Utilities.h"

Entity MonsterType::CreateInstance(
  int x, int y
) const {
  return Entity{this, x, y};
}

namespace {
  FightingStyle StringToFightingStyle(const std::string& StyleStr) {
    if (StyleStr == "BruteForce") {
      return FightingStyle::BruteForce;
    }
    if (StyleStr == "RangedSnipe") {
      return FightingStyle::RangedSnipe;
    }

    return FightingStyle::Swarm;
  }
}

Bestiary MonsterType::LoadMonsterTypes() {
  char *Raw{static_cast<char*>(SDL_LoadFile("types.txt", nullptr))};

  std::string Data(Raw);
  SDL_free(Raw);

  Bestiary MonsterTypes;
  using namespace Utilities;
  for (std::string& Line : SplitString(Data, '\n')) {
    std::vector<std::string> Fields{SplitString(Line, ',')};

    MonsterTypes.push_back({
      Fields[0],
      std::stoi(Fields[1]),
      std::stoi(Fields[2]),
      std::stoi(Fields[3]),
      Fields[4],
      StringToFightingStyle(Fields[5])
    });
  }

  return MonsterTypes;
}

