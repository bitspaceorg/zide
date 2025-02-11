#pragma once

#include <string>
#include <variant>

#include "rgb.h"
#include "hsl.h"
#include "hsv.h"

struct Color {
public:
  enum class Format { MASK, RGB, HEX, HSL, HSV };

  Color();
  static Color fromMask(); // TRANSPERANT TYPE
  static Color fromRgb(int red, int green, int blue, int alpha = 255);
  static Color fromHsv(double hue, double saturation, double value);
  static Color fromHsl(double hue, double saturation, double lightness);
  static Color fromHex(std::string hexcode);

  int    getRed();
  int    getGreen();
  int    getBlue();
  double getHue();
  double getHSVSaturation();
  double getHSLSaturation();
  double getValue();
  double getLightness();

private:
  Color(Format format);
  Format m_currentFormat;
  std::variant<RGB, HSV, HSL> m_value;
};
