#include "hsl.h"

#include "hsv.h"
#include "rgb.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <ostream>

HSL::HSL(const RGB &rgb) {
  const double red = rgb.getRed() / 255.0, green = rgb.getGreen() / 255.0,
               blue = rgb.getBlue() / 255.0;
  const double max = std::max({red, green, blue});
  const double min = std::min({red, green, blue});

  const double range = max - min;
  const double L = (0.5 * min) + (0.5 * max);

  double _hue;
  if (range == 0)
    _hue = 0;
  else if (max == red)
    _hue = std::fmod(((green - blue) / range), 6);
  else if (max == green)
    _hue = ((blue - red) / range) + 2;
  else if (max == blue)
    _hue = ((red - green) / range) + 4;

  this->m_hue = _hue * 60;
  this->m_lightness = (0.5 * (max + min));
  this->m_saturation =
      (L == 0 || L == 1) ? 0 : range / (1 - std::abs(2 * L - 1));

  this->m_lightness = std::clamp(m_lightness, 0.0, 1.0) * 100;
  this->m_saturation = std::clamp(m_saturation, 0.0, 1.0) * 100;
};

HSL::HSL(const HSV &hsv) {
  const double saturation = hsv.getSaturation() / 100.0;
  const double value = hsv.getValue() / 100.0;

  this->m_hue = hsv.getHue();
  this->m_lightness = value * (1 - saturation / 2.0);
  this->m_saturation =
      (m_lightness == 0 || m_lightness == 1)
          ? 0
          : ((value - m_lightness) / std::min(m_lightness, 1.0 - m_lightness));

  this->m_lightness = std::round(m_lightness * 100);
  this->m_saturation = std::round(m_saturation * 100);
};

double HSL::getHue() const { return this->m_hue; };
double HSL::getSaturation() const { return this->m_saturation; };
double HSL::getLightness() const { return this->m_lightness; };
