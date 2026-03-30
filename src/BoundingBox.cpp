#include <SDL3/SDL.h>
#include "BoundingBox.h"

void BoundingBox::Render(SDL_Surface* Surface) {
  const auto* Fmt{SDL_GetPixelFormatDetails(
    Surface->format
  )};

  Uint32 LineColor{
    SDL_MapRGB(Fmt, nullptr, 220, 0, 0)};

  SDL_Rect Rounded{Round(Rect)};
  auto [x, y, w, h]{Rounded};

  int LineWidth{4};
  SDL_Rect Top{x, y, w, LineWidth};
  SDL_Rect Bottom{x, y + h - LineWidth, w, LineWidth};
  SDL_Rect Left{x, y, LineWidth, h};
  SDL_Rect Right{x + w - LineWidth, y, LineWidth, h};

  SDL_FillSurfaceRect(Surface, &Top, LineColor);
  SDL_FillSurfaceRect(Surface, &Bottom, LineColor);
  SDL_FillSurfaceRect(Surface, &Left, LineColor);
  SDL_FillSurfaceRect(Surface, &Right, LineColor);
}
