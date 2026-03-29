#pragma once
#include <cmath>
#include <iostream>


struct Vec2{
  float x;
  float y;

  float GetLength() const {
    return std::sqrt(x * x + y * y);
  }

  Vec2 Normalize() const {
    float Length{GetLength()};
    if (Length == 0.0f) {
      return Vec2{0, 0};
    }

    return *this / Length;
  }
 
  float GetDistance(const Vec2& Other) const {
    return std::sqrt(
      std::pow(x - Other.x, 2) +
      std::pow(y - Other.y, 2)
    );
  }

  Vec2 operator*(float Multiplier) const {
    return Vec2{
      x * Multiplier,
      y * Multiplier
    };
  }

  Vec2 operator/(float Divisor) const {
    if (Divisor == 0.0f) {
      return Vec2{0, 0};
    }

    return Vec2 {
      x / Divisor,
      y / Divisor
    };
  }

  Vec2& operator*=(float Multiplier) {
    x *= Multiplier;
    y *= Multiplier;

    return *this;
  }

  Vec2& operator/=(float Divisor) {
    x /= Divisor;
    y /= Divisor;

    return *this;
  }

  Vec2 operator-() const {
    return {-x, -y};
  }

  Vec2 operator+(const Vec2& Other) const {
    return Vec2 {
      x + Other.x,
      y + Other.y
    };
  }

  Vec2 operator-(const Vec2& Other) const {
    return Vec2 {
      x - Other.x,
      y - Other.y
    };
  }

  Vec2 &operator+=(const Vec2& Other) {
    x += Other.x;
    y += Other.y;

    return *this;
  }

  Vec2 &operator-=(const Vec2& Other) {
    x -= Other.x;
    y -= Other.y;

    return *this;
  }

  float Dot(const Vec2& Other) const {
    return (x * Other.x) + (y * Other.y);
  }
};

inline Vec2 operator*(float M, const Vec2& V) {
  return V * M;
}

inline std::ostream& operator <<(std::ostream& Stream, const Vec2& V) {
  Stream << "{ x = " << V.x << ", y = " << V.y << " }\n";
  return Stream;
}
