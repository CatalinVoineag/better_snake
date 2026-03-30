#include <SDL3/SDL.h>
#include "GameObject.h"
#include <iostream>
#include "Scene.h"

#define DRAW_DEBUG_HELPERS

#ifdef DRAW_DEBUG_HELPERS
namespace{
SDL_Surface* Trajectories{
  SDL_CreateSurface(
    700, 300,
    SDL_PIXELFORMAT_RGBA32
  )};
}
#endif

void GameObject::Render(SDL_Surface* Surface) {
#ifdef DRAW_DEBUG_HELPERS
  SDL_Rect PositionIndicator{
    int(Position.x) - 10, int(Position.y) - 10, 20, 20};

  SDL_FillSurfaceRect(
    Trajectories,
    &PositionIndicator,
    SDL_MapRGB(
      SDL_GetPixelFormatDetails(Trajectories->format),
      nullptr, 220, 0, 0
    )
  );

  SDL_BlitSurface(
    Trajectories, nullptr,
    Surface, nullptr);
  
  Bounds.Render(Surface);
#endif
  ImageClass.Render(Surface, Position);
}

void GameObject::Tick(float DeltaTime) {
  CalculateAnimation();
  if (SceneClass.GetPlayerCharacter().GetPosition()
      .GetDistance(Position) > 20.0f * PIXELS_PER_METER
  ) {
    return;
  }

  ApplyForce(GetFrictionForce(DeltaTime));
  ApplyForce(GetDragForce());

  if (ForceTimeRemaining > 0) {
    ApplyForce({10000, 0});
    ForceTimeRemaining -= DeltaTime;
  }

  Velocity += Acceleration * DeltaTime;
  Position += Velocity * DeltaTime;
  Acceleration = {0, 9.8f * PIXELS_PER_METER};
  Clamp(Velocity);

  // Don't fall through the floor
  if (Position.y > 200) {
    Position.y = 200;
    Velocity.y = 0;
  }
  Bounds.SetPosition(Position);
}

void GameObject::CalculateAnimation(){
  SDL_Rect BoundingBoxRect{BoundingBox::Round(Bounds.GetRect())};

  SDL_Rect ViewPortRect{SceneClass.GetViewport()};

  if (!SDL_HasRectIntersection(&ViewPortRect, &BoundingBoxRect)) {
    std::cout << "Not visiable - skip \n";
    return;
  }

  std::cout << "Animating \n";
}
