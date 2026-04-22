#include <iostream>
#include <algorithm>
#include "ImageComponent.h" 
#include "TransformComponent.h" 
#include "Entity.h" 
#include "AssetManager.h" 
#include "Utilities.h" 

namespace {
  struct BlitInfo {
    SDL_Rect SourceRect;
    SDL_Rect DestRect;
  };
  
  BlitInfo CalculateBlitInfo(
    ScalingMode Mode,
    // Natural surface dimension
    int SurfaceW, int SurfaceH,
    // Target top-left screen position
    float TargetX, float TargetY,
    // Target rendering dimensions
    float TargetW, float TargetH
  ) {
    BlitInfo Info;
    // Default to rendering the whole image
    Info.SourceRect = {0, 0, SurfaceW, SurfaceH};

    if (Mode == ScalingMode::None) {
      // Render at natural size
      // and at target position
      Info.DestRect = Utilities::Round({
        TargetX,
        TargetY,
        static_cast<float>(SurfaceW),
        static_cast<float>(SurfaceH),
      });
      return Info;
    } else if (Mode == ScalingMode::Fill) {
      // Stretch source to fill the exact target dimensions
      Info.DestRect = Utilities::Round({
        TargetX, TargetY, TargetW, TargetH
      });
      return Info;
    } else if (Mode == ScalingMode::Contain) {
      float Scale{std::min(TargetW / SurfaceW, TargetH / SurfaceH)};

      Info.DestRect = Utilities::Round({
        TargetX, TargetY,
        SurfaceW * Scale,
        SurfaceH * Scale
      });

      return Info;
    } else if (Mode == ScalingMode::Cover) {
      float Scale{std::max(TargetW / SurfaceW, TargetH / SurfaceH)};

      if (Scale* SurfaceW > TargetW) {
        float ClipW{TargetW / Scale};
        Info.SourceRect = Utilities::Round({
          0, 0,
          ClipW,
          static_cast<float>(SurfaceH)
        });
      } else if (Scale * SurfaceH > TargetH) {
        float ClipH{TargetH / Scale};
        Info.SourceRect = Utilities::Round({
          0, 0,
          static_cast<float>(SurfaceW),
          ClipH
        });
      }

      Info.DestRect = Utilities::Round({
        TargetX,
        TargetY,
        TargetW,
        TargetH
      });

      return Info;
    }
    
    std::cerr << "Error: Unknown Scaling mode\n";
    return Info;
  }
}

void ImageComponent::Initialize() {
  Entity* Owner{GetOwner()};
  if (!Owner->GetTransformComponent()) {
    std::cout << "Error: ImageComponent requires"
      " TransformComponent on its Owner\n";

    // Request removal
    Owner->RemoveComponent(this);
  }
}

ImageComponent::ImageComponent(
  Entity* Owner,
  const std::string& FilePath
) : Component(Owner), ImageFilePath(FilePath) {
  // Load the image from the file path 
  ImageSurface = GetAssetManager().LoadSurface(ImageFilePath);

  // Check if IMG_Load returned a valid surface pointer
  if (!ImageSurface) {
    // If null, loading failed. Print an error.
    std::cerr << "Failed to load image: " << FilePath << " Error " << SDL_GetError() << '\n';
  } else {
    // Loading succeeded!
    std::cout << "Loaded image: " << FilePath << '\n';
  }
}

void ImageComponent::Render(SDL_Surface* Surface) {
  if (!ImageSurface) return;

  auto[TargetX, TargetY]{GetOwnerPosition() + Offset};
  float TargetW{GetWidth() * GetOwnerScale()};
  float TargetH{GetHeight() * GetOwnerScale()};

  int SurfaceW{GetSurfaceWidth()};
  int SurfaceH{GetSurfaceHeight()};

  BlitInfo Info{CalculateBlitInfo(
    ScaleMode,
    SurfaceW, SurfaceH,
    TargetX, TargetY,
    TargetW, TargetH
  )};

  if (
    !SDL_BlitSurfaceScaled(
      ImageSurface.get(),
      &Info.SourceRect,
      Surface,
      &Info.DestRect,
      SDL_SCALEMODE_LINEAR
    )
  ) {
    std::cerr << "Error: Blit failed: " << SDL_GetError() << "\n";
  }

}

void ImageComponent::SetWidth(float NewWidth) {
  Width = NewWidth;
}

void ImageComponent::SetHeight(float NewHeight) {
  Height = NewHeight;
}

void ImageComponent::ResetWidth() {
  Width = std::nullopt;
}

void ImageComponent::ResetHeight() {
  Height = std::nullopt;
}

float ImageComponent::GetWidth() const {
  return Width.value_or(GetSurfaceWidth());
}

float ImageComponent::GetHeight() const {
  return Height.value_or(GetSurfaceHeight());
}

void ImageComponent::SetScalingMode(ScalingMode Mode) {
  ScaleMode = Mode;
}

bool ImageComponent::LoadNewImage(const std::string& NewPath) {
  ImageFilePath = NewPath;
  ImageSurface = GetAssetManager().LoadSurface(NewPath);

  return ImageSurface != nullptr;
}

int ImageComponent::GetSurfaceWidth() const {
  if (!ImageSurface) {
    std::cerr << "Warning: Attempted to get width from null ImageSurface\n" ;
    return 0;
  }

  return ImageSurface->w;
}

int ImageComponent::GetSurfaceHeight() const {
  if (!ImageSurface) {
    std::cerr << "Attempted to get height from null ImageSurface\n";
    return 0;
  }

  return ImageSurface->h;
}

void ImageComponent::DrawDebugHelpers(SDL_Surface* Surface) {
  using Utilities::DrawRectOutline;
  if (!ImageSurface) return;

  auto[TargetX, TargetY]{GetOwnerPosition() + Offset};
  float OwnerScale{GetOwnerScale()};
  float TargetW{GetWidth() * OwnerScale};
  float TargetH{GetHeight() * OwnerScale};
  int SurfaceW{GetSurfaceWidth()};
  int SurfaceH{GetSurfaceHeight()};

  // 1. Draw the natural bounds green outline
  SDL_Rect NaturalBounds{
    Utilities::Round({
      TargetX, TargetY,
      SurfaceW * OwnerScale,
      SurfaceH * OwnerScale
    })
  };

  DrawRectOutline(
    Surface, NaturalBounds,
    SDL_MapRGB(
      SDL_GetPixelFormatDetails(Surface->format),
      nullptr, 0, 255, 0
    )
  );

  // 2. Draw Rendered Bounds (Red outline)
  
  BlitInfo Info{CalculateBlitInfo(
    ScaleMode,
    SurfaceW, SurfaceH,
    TargetX, TargetY,
    TargetW, TargetH
  )};

  DrawRectOutline(
    Surface, Info.DestRect,
    SDL_MapRGB(
      SDL_GetPixelFormatDetails(Surface->format),
      nullptr, 255, 0,0
    )
  );

  SDL_Rect DebugRect{Utilities::Round({TargetX-5, TargetY-5, 10, 10})};

  SDL_FillSurfaceRect(
    Surface,
    &DebugRect,
    SDL_MapRGB(
      SDL_GetPixelFormatDetails(Surface->format),
      nullptr, 0, 0, 255
    )
  );
}
