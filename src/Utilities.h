// Utilities.h
#pragma once
#include <sstream>
#include <vector>
#include <string>

namespace Utilities{
  inline std::vector<std::string> SplitString(
    const std::string& Str, char Delimiter
  ) {
    std::vector<std::string> Tokens;
    std::string Token;
    std::istringstream TokenStream(Str);

    while (std::getline(
      TokenStream, Token, Delimiter
    )) {
      Tokens.push_back(Token);
    }
    return Tokens;
  }
}
