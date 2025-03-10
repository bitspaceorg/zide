#include <cassert>
#include <iostream>
#include <variant>

#include "color.h"
#include "hsl.h"
#include "hsv.h"
#include "rgb.h"

Color::Color(Format format) { this->m_currentFormat = format; };
Color::Color() { this->m_currentFormat = Format::MASK; };

Color Color::fromMask() {
  Color currentColor = Color(Color::Format::RGB);
  currentColor.m_value = RGB(0, 0, 0, 0);

  return currentColor;
};

Color Color::fromRgb(int red, int green, int blue, int alpha) {
  assert(red >= 0 && red < 256);
  assert(green >= 0 && green < 256);
  assert(blue >= 0 && blue < 256);

  Color currentColor = Color(Color::Format::RGB);
  currentColor.m_value = RGB(red, green, blue, alpha);

  return currentColor;
};

Color Color::fromHsv(double hue, double saturation, double value) {
  assert(hue >= 0 && hue < 360);
  assert(saturation >= 0 && saturation <= 100);
  assert(value >= 0 && value <= 100);

  Color currentColor = Color(Color::Format::HSV);
  currentColor.m_value = HSV(hue, saturation, value);

  return currentColor;
};

Color Color::fromHsl(double hue, double saturation, double lightness) {
  assert(hue >= 0 && hue < 360);
  assert(saturation >= 0 && saturation <= 100);
  assert(lightness >= 0 && lightness <= 100);

  Color currentColor = Color(Color::Format::HSL);
  currentColor.m_value = HSL(hue, saturation, lightness);

  return currentColor;
};

const int HEX_SIZE = 16;
Color Color::fromHex(std::string hexcode) {
  assert(hexcode.size() == 7 || hexcode.size() == 9);
  assert(hexcode[0] == '#');

  int red = std::stoi(hexcode.substr(1, 2), 0, HEX_SIZE);
  int green = std::stoi(hexcode.substr(3, 2), 0, HEX_SIZE);
  int blue = std::stoi(hexcode.substr(5, 2), 0, HEX_SIZE);

  assert(red >= 0 && red < 256);
  assert(green >= 0 && green < 256);
  assert(blue >= 0 && blue < 256);

  Color currentColor = Color(Color::Format::RGB);
  currentColor.m_value = RGB(red, green, blue);

  return currentColor;
};

int Color::getRed() {
  auto visitor = [](auto &&arg) -> int {
    using T = std::decay_t<decltype(arg)>;

    if constexpr (std::is_same_v<T, RGB>) {
      return arg.getRed();
    } else if constexpr (std::is_same_v<T, HSL>) {
      return RGB(arg).getRed();
    } else if constexpr (std::is_same_v<T, HSV>) {
      return RGB(arg).getRed();
    };
    return 0;
  };

  return std::visit(visitor, this->m_value);
};

int Color::getBlue() {
  auto visitor = [](auto &&arg) -> int {
    using T = std::decay_t<decltype(arg)>;

    if constexpr (std::is_same_v<T, RGB>) {
      return arg.getBlue();
    } else if constexpr (std::is_same_v<T, HSL>) {
      return RGB(arg).getBlue();
    } else if constexpr (std::is_same_v<T, HSV>) {
      return RGB(arg).getBlue();
    };
  };

  return std::visit(visitor, this->m_value);
};

int Color::getGreen() {
  auto visitor = [](auto &&arg) -> int {
    using T = std::decay_t<decltype(arg)>;

    if constexpr (std::is_same_v<T, RGB>) {
      return arg.getGreen();
    } else if constexpr (std::is_same_v<T, HSL>) {
      return RGB(arg).getGreen();
    } else if constexpr (std::is_same_v<T, HSV>) {
      return RGB(arg).getGreen();
    };
  };

  return std::visit(visitor, this->m_value);
};

int Color::getAlpha() {
  auto visitor = [](auto &&arg) -> int {
    using T = std::decay_t<decltype(arg)>;

    if constexpr (std::is_same_v<T, RGB>) {
      return arg.getAlpha();
    } else if constexpr (std::is_same_v<T, HSL>) {
      return RGB(arg).getAlpha();
    } else if constexpr (std::is_same_v<T, HSV>) {
      return RGB(arg).getAlpha();
    };
  };

  return std::visit(visitor, this->m_value);
};

double Color::getHue() {
  auto visitor = [](auto &&arg) -> double {
    using T = std::decay_t<decltype(arg)>;

    if constexpr (std::is_same_v<T, RGB>) {
      return HSV(arg).getHue();
    } else if constexpr (std::is_same_v<T, HSL>) {
      return arg.getHue();
    } else if constexpr (std::is_same_v<T, HSV>) {
      return arg.getHue();
    };
  };

  return std::visit(visitor, this->m_value);
};

double Color::getHSVSaturation() {
  auto visitor = [](auto &&arg) -> double {
    using T = std::decay_t<decltype(arg)>;

    if constexpr (std::is_same_v<T, RGB>) {
      return HSV(arg).getSaturation();
    } else if constexpr (std::is_same_v<T, HSL>) {
      return HSV(arg).getSaturation();
    } else if constexpr (std::is_same_v<T, HSV>) {
      return arg.getSaturation();
    };
  };

  return std::visit(visitor, this->m_value);
};

double Color::getHSLSaturation() {
  auto visitor = [](auto &&arg) -> double {
    using T = std::decay_t<decltype(arg)>;

    if constexpr (std::is_same_v<T, RGB>) {
      return HSL(arg).getSaturation();
    } else if constexpr (std::is_same_v<T, HSL>) {
      return arg.getSaturation();
    } else if constexpr (std::is_same_v<T, HSV>) {
      return HSL(arg).getSaturation();
    };
  };

  return std::visit(visitor, this->m_value);
};

double Color::getLightness() {
  auto visitor = [](auto &&arg) -> double {
    using T = std::decay_t<decltype(arg)>;

    if constexpr (std::is_same_v<T, RGB>) {
      return HSL(arg).getLightness();
    } else if constexpr (std::is_same_v<T, HSL>) {
      return arg.getLightness();
    } else if constexpr (std::is_same_v<T, HSV>) {
      return HSL(arg).getLightness();
    };
  };

  return std::visit(visitor, this->m_value);
};

double Color::getValue() {
  auto visitor = [](auto &&arg) -> double {
    using T = std::decay_t<decltype(arg)>;

    if constexpr (std::is_same_v<T, RGB>) {
      return HSV(arg).getValue();
    } else if constexpr (std::is_same_v<T, HSL>) {
      return HSV(arg).getValue();
    } else if constexpr (std::is_same_v<T, HSV>) {
      return arg.getValue();
    };
  };

  return std::visit(visitor, this->m_value);
};
