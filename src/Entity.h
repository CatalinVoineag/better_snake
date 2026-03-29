#pragma once
#include <iostream>
#include "MonsterType.h"

class Entity {
public:
  Entity(const MonsterType* Type, int x, int y)
    : Type{Type}, X_Pos{x}, Y_Pos{y},
      CurrentHealth{Type ? Type->MaxHealth : 0} {}

  const MonsterType* Type;

  void ChangeType(const MonsterType* NewType) {
    if (!NewType) return; // Or handle error

    std::cout << X_Pos << "," << Y_Pos << ": "
      << Type->Name
      << " is transforming into a "
      << NewType->Name << "!\n";
    Type = NewType;

    CurrentHealth = Type->MaxHealth;
  }

  void Render() {
    if (!Type) {
      // Handle error
      return;
    }
    std::cout << X_Pos << "," << Y_Pos
      << ": Rendering " << Type->Name
      << " using art file: " << Type->ArtFile
      << "\n";
  }

  int X_Pos;
  int Y_Pos;
  int CurrentHealth;
};
