#pragma once
#define CHECK_ERRORS

#include<iostream>
#include<SDL3/SDL.h>
#include<string>

namespace Config {
  // Game Settings
  inline const std::string GAME_NAME{"Snake"};
  inline constexpr int GRID_COLUMNS{16};
  static_assert(
    GRID_COLUMNS >= 12,
    "Grid must be a at least 12 columns wide"
  );

  inline constexpr int GRID_ROWS{5};
  static_assert(GRID_ROWS >= 5, "Grid must be at least 5 rows tall");

  // Size and Positioning
  inline constexpr int PADDING{5};
  inline constexpr int CELL_SIZE{36};
  inline constexpr int GRID_HEIGHT{CELL_SIZE * GRID_ROWS};
  inline constexpr int GRID_WIDTH{CELL_SIZE * GRID_COLUMNS};

  inline constexpr int WINDOW_HEIGHT{GRID_HEIGHT + PADDING * 2};
  inline constexpr int WINDOW_WIDTH{GRID_WIDTH + PADDING * 2};

  // Colors
  inline constexpr SDL_Color BACKGROUND_COLOR{85, 138, 52, 255};
  inline constexpr SDL_Color FONT_COLOR{255, 255, 255, 255};

  // Asset Paths
  inline const std::string BASE_PATH{SDL_GetBasePath()};
  inline const std::string APPLE_IMAGE{BASE_PATH + "apple.png"};
  inline const std::string FONT{BASE_PATH + "Rubik-SemiBold.ttf"};

  inline void CheckSDLError(const std::string& Msg) {
#ifdef CHECK_ERRORS
    const char* error = SDL_GetError();
    if (*error != '\0') {
      std::cerr << Msg << " Error: " << error << '\n';
      SDL_ClearError();
    }
#endif
  }
}
