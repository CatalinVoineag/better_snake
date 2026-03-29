#pragma once
#include <string>
#include <vector>

class Entity;
struct MonsterType;
using Bestiary = std::vector<MonsterType>;

enum class FightingStyle {
  Swarm, BruteForce, RangedSnipe
};

struct MonsterType {
  std::string Name;
  int Level;
  int MaxHealth;
  int Damage;
  std::string ArtFile;
  FightingStyle Style;

  Entity CreateInstance(int x, int y) const;
  static Bestiary LoadMonsterTypes();
};
