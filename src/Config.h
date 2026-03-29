#pragma once
#include <iostream>
#include <vector>
#include <SDL3/SDL.h>
#include <iostream>

inline constexpr float PIXELS_PER_METER{50.0f};

struct Config{
  std::string WindowTitle;
  int WindowWidth;
  int WindowHeight;
  std::vector<int> Levels;


  void Load(const std::string& Path) {
    std::string FilePath{std::string(Path)};

    std::string Content{ReadFile(FilePath)};
    if (Content.empty()) return;
    ParseConfig(Content);
  }

private:
  std::string ReadFile(const std::string& Path) {
    SDL_IOStream* File{SDL_IOFromFile(Path.c_str(), "rb")};

    if (!File) {
    std::cout << "Failed to open config file: "
        << SDL_GetError() << "\n";
      return "";
    }

    Sint64 Size{SDL_GetIOSize(File)};
    std::string Content(Size, '\0');
    SDL_ReadIO(File, Content.data(), Size);
    SDL_CloseIO(File);
    return Content;
  }

  void ParseConfig(const std::string& Content){
    size_t Start{0};
    size_t End{Content.find("\n", Start)};

    while (End != std::string::npos) {
      ProcessLine(Content.substr(Start, End - Start));
      Start = End + 1;
      End = Content.find("\n", Start);
    }

    ProcessLine(Content.substr(Start));
  }

  void ProcessLine(const std::string& Line) {
    size_t Delim{Line.find(": ")};
    if (Delim == std::string::npos) return;

    std::string Key{Line.substr(0, Delim)};
    std::string Value{Line.substr(Delim + 2)};

    if (Key == "WINDOW_TITLE") {
      WindowTitle = Value;
    } else if (Key == "WINDOW_WIDTH") {
      WindowWidth = std::stoi(Value);
    } else if (Key == "WINDOW_WIDTH") {
      WindowHeight = std::stoi(Value);
    } else if (Key == "LEVELS") {
      ParseLevels(Value);
    }
  }

  void ParseLevels(const std::string& Value) {
    Levels.clear();
    size_t Start{0};
    size_t End{Value.find(",", Start)};

    while (End != std::string::npos) {
      Levels.push_back(std::stoi(Value.substr(Start, End - Start)));
      Start = End + 1;
      End = Value.find(",", Start);
    }

    Levels.push_back(std::stoi(Value.substr(Start)));
  }
};
