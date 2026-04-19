#pragma once
#include <SDL3/SDL.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <iostream>
#include <SDL3_image/SDL_image.h>

// Custom deleter for an SDL_Surface
struct SDLSurfaceDeleter {
  void operator()(SDL_Surface* Surface) const {
    SDL_DestroySurface(Surface);
  }
};

using SurfacePtr = std::shared_ptr<SDL_Surface>;

// Map file path to shared surface pointer
using CacheMap = std::unordered_map<std::string, SurfacePtr>;

class AssetManager {
  public:
  AssetManager() = default;
  //Prevent copying/moving
  AssetManager(const AssetManager&) = delete;
  AssetManager& operator=(const AssetManager&) = delete;
  AssetManager(AssetManager&&) = delete;
  AssetManager& operator=(AssetManager&&) = delete;

  // Load a surface, resuse
  SurfacePtr LoadSurface(const std::string& Path) {
    if (SurfaceCache.contains(Path)) {
      std::cout << "Chace hit \n";
      return SurfaceCache[Path];
    }

    std::cout << "Cahche miss \n";

    SDL_Surface* Surface{IMG_Load(Path.c_str())};
    if (!Surface) {
      std::cerr << "AssetManager failed to load:"
                << Path << " Error: "
                << SDL_GetError() << '\n';

      return nullptr;
    }

    SurfacePtr SharedSurface(Surface, SDLSurfaceDeleter{});

    // Sotre in cache and return
    SurfaceCache[Path] = SharedSurface;
    return SharedSurface;
  }

  private:
    CacheMap SurfaceCache;
};
