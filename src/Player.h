#pragma once
#include <string>
#include <iostream>
#include <SDL3/SDL.h>

class Player {
public:
  std::string Name;
  int Level;
  float Health;

  void SaveToFile(const std::string& Path) {
    SDL_IOStream* Handle{SDL_IOFromFile(Path.c_str(), "wb")};

    if (!Handle) {
      std::cout << "Error opening file: "
        << SDL_GetError();
      return;
    }

    std::string LevelStr{std::to_string(Level)};
    std::string HealthStr{std::to_string(Health)};

    SDL_WriteIO(Handle, Name.c_str(), Name.length());
    SDL_WriteIO(Handle, ",", 1);

    SDL_WriteIO(Handle, LevelStr.c_str(), LevelStr.length());
    SDL_WriteIO(Handle, ",", 1);

    SDL_WriteIO(Handle, HealthStr.c_str(), HealthStr.length());
    SDL_WriteIO(Handle, ",", 1);

    SDL_CloseIO(Handle);
  }
};
