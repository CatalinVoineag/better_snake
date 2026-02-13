#pragma once
#include <SDL3/SDL.h>
#include "Assets.h"
#include "Engine/Text.h"

class ScoreCounter {
public:
  ScoreCounter(Assets& Assets) : AssetList{Assets} {}
  void HandleEvent(const SDL_Event& E) {
    if (E.type == UserEvents::APPLE_EATEN) {
      CurrentScore++;
      Text.SetText(GetScoreString());
    } else if (E.type == UserEvents::RESTART_GAME) {
      CurrentScore = 0;
      Text.SetText(GetScoreString());
    }
  }
  void Render(SDL_Surface* Surface) {
    using namespace Config;
    SDL_FillSurfaceRect(Surface, &BackgroundRect,
      SDL_MapRGB(
        SDL_GetPixelFormatDetails(Surface->format),
        nullptr,
        SCORE_BACKGROUND_COLOR.r,
        SCORE_BACKGROUND_COLOR.g,
        SCORE_BACKGROUND_COLOR.b
      )
    );
    // AssetList.Apple.Render(Surface, &AppleRect);
    Text.Render(Surface, &TextRect);
  }

private:
  std::string GetScoreString() {
    return std::to_string(CurrentScore) + "/" + std::to_string(MaxScore);
  }

  Assets& AssetList;
  int MaxScore{Config::MAX_LENGTH - 2};
  int CurrentScore{0};
  SDL_Rect BackgroundRect{
    Config::PADDING,
    Config::GRID_HEIGHT + Config::PADDING * 2,
    MaxScore > 99 ? 250 : 190,
    Config::FOOTER_HEIGHT - Config::PADDING
  };
  SDL_Rect AppleRect{
    BackgroundRect.x + Config::PADDING,
    BackgroundRect.y + Config::PADDING,
    BackgroundRect.w + Config::PADDING * 2,
    BackgroundRect.h + Config::PADDING * 2
  };
  SDL_Rect TextRect {
    BackgroundRect.x + Config::PADDING * 4,
    BackgroundRect.y + Config::PADDING,
    BackgroundRect.w + Config::PADDING * 2,
    BackgroundRect.h + Config::PADDING * 2
  };
  Engine::Text Text{GetScoreString(), 40};
};
