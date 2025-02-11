#include "rgb.h"
#include "hsl.h"
#include "hsv.h"

#include <algorithm>
#include <cmath>

/* the algorithm is converts hsl value to
 * RGB value, and i've use the below blog
 * as reference
 *
 * https://www.baeldung.com/cs/convert-color-hsl-rgb
 */
RGB::RGB(const HSL &hsl) {
  const double hue = hsl.getHue(), saturation = hsl.getSaturation() / 100,
               lightness = hsl.getLightness() / 100;

  const double chroma = (1 - std::abs(2 * lightness - 1)) * saturation;
  const double _hue = hue / 60;

  const double X = chroma * (1.0 - std::abs(std::fmod(_hue, 2.0) - 1.0));

  /* Temp RGB, that are decimals lie between [0,1] */
  double dR = 0, dG = 0, dB = 0;
  if (_hue >= 0 && _hue <= 1) {
    dR = chroma, dG = X;
  } else if (_hue <= 2) {
    dR = X, dG = chroma;
  } else if (_hue <= 3) {
    dG = chroma, dB = X;
  } else if (_hue <= 4) {
    dG = X, dB = chroma;
  } else if (_hue <= 5) {
    dR = X, dB = chroma;
  } else if (_hue <= 6) {
    dR = chroma, dB = X;
  };

  double m = lightness - chroma / 2.0;

  dR = (dR + m) * 255;
  dG = (dG + m) * 255;
  dB = (dB + m) * 255;

  this->m_red   = std::round(dR);
  this->m_green = std::round(dG);
  this->m_blue  = std::round(dB);
};

/* the algorithm is converts HSV value to
 * RGB value, and i've use the below blog
 * as reference
 *
 * https://www.rapidtables.com/convert/color/hsv-to-rgb.html
 */
RGB::RGB(const HSV &hsv) {
  const double _hue = hsv.getHue() / 60, saturation = hsv.getSaturation() / 100,
               value = hsv.getValue() / 100;
  double chroma = saturation * value;
  double X = chroma * (1.0 - std::abs(std::fmod(_hue, 2.0) - 1));
  double m = value - chroma;

  double dR = 0, dG = 0, dB = 0;
  if (_hue >= 0 && _hue <= 1) {
    dR = chroma, dG = X;
  } else if (_hue <= 2) {
    dR = X, dG = chroma;
  } else if (_hue <= 3) {
    dG = chroma, dB = X;
  } else if (_hue <= 4) {
    dG = X, dB = chroma;
  } else if (_hue <= 5) {
    dR = X, dB = chroma;
  } else if (_hue <= 6) {
    dR = chroma, dB = X;
  };

  dR = (dR + m) * 255;
  dG = (dG + m) * 255;
  dB = (dB + m) * 255;

  this->m_red = std::round(dR);
  this->m_green = std::round(dG);
  this->m_blue = std::round(dB);
};

double RGB::getRed() const { return this->m_red; };
double RGB::getGreen() const { return this->m_green; };
double RGB::getBlue() const { return this->m_blue; };
double RGB::getAlpha() const { return this->m_alpha; };
