#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include <SDL3/SDL_iostream.h>

namespace File {
  void Read(const std::string& Path) {
    char* Content{static_cast<char*>(
      SDL_LoadFile(Path.c_str(), nullptr)
    )};

    if (Content) {
      std::cout << "Content: " << Content << "\n";
    } else {
      std::cout << "Error loading file: "
        << SDL_GetError();
    }

    SDL_free(Content);
  }

  void Write(const std::string& Path, const std::vector<std::string>& Values) {
    SDL_IOStream* Handle{
      SDL_IOFromFile(Path.c_str(), "wb")
    };

    if (!Handle) {
      std::cout << "Error opening file: " << SDL_GetError();
    }

    for (size_t i = 0; i < Values.size(); ++i) {
      const std::string& Value{Values[i]};
      SDL_WriteIO(Handle, Value.c_str(), Value.length());

      if (i < Value.size() - 1) {
        SDL_WriteIO(Handle, ",", 1);
      } else {
        SDL_WriteIO(Handle, "\n", 1);
      }
    }

    SDL_CloseIO(Handle);
  }
}
