#pragma once
#include <SDL3/SDL.h>
#include <cmath>
#include "Vec2.h"

class BoundingBox {
public:
  BoundingBox(const SDL_FRect& InitialRect)
  : Rect{InitialRect} {}

  void SetPosition(const Vec2& Position) {
    Rect.x = Position.x;
    Rect.y = Position.y;
  }

  static SDL_Rect Round(const SDL_FRect& Rect) {
    return {
      static_cast<int>(std::round(Rect.x)),
      static_cast<int>(std::round(Rect.y)),
      static_cast<int>(std::round(Rect.w)),
      static_cast<int>(std::round(Rect.h))
    };
  }

 void Render(SDL_Surface* Surface);

 bool GetIntersection(const BoundingBox& Other, SDL_FRect* Intersection) {
   if (!Intersection) return false;

   SDL_FRect A{GetRect()};
   SDL_FRect B{Other.GetRect()};

   if (!SDL_GetRectIntersectionFloat(&A, &B, Intersection)) {
     return false;
   }

   if (SDL_RectEmptyFloat(Intersection)) {
     return false;
   }

   return true;
 }

 SDL_FRect GetRect() const {
   return Rect;
 } 

private:
  SDL_FRect Rect;
};
