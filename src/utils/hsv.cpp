#include "hsv.h"
#include "hsl.h"
#include "rgb.h"

#include <algorithm>
#include <cmath>
#include <iostream>

/* This algorithm converts RGB from parameter to
 * HSV. The algorithm is reference from the following
 * document.
 *
 * https://en.wikipedia.org/wiki/HSL_and_HSV
 *
 */
HSV::HSV(const RGB &rgb) {
  const double red = rgb.getRed() / 255.0, green = rgb.getGreen() / 255.0,
               blue = rgb.getBlue() / 255.0;
  const double max = std::max({red, green, blue});
  const double min = std::min({red, green, blue});

  const double range = max - min;

  double _hue;
  if (range == 0)
    _hue = 0;
  else if (max == red)
    _hue = std::fmod(((green - blue) / range), 6);
  else if (max == green)
    _hue = ((blue - red) / range) + 2;
  else if (max == blue)
    _hue = ((red - green) / range) + 4;

  this->m_hue = (_hue >= 0) ? _hue * 60 : 360 + (_hue * 60);
  this->m_value = max * 100;
  this->m_saturation = (m_value == 0) ? 0 : (range / max) * 100;

  this->m_hue = std::round(m_hue);
  this->m_value = std::round(m_value);
  this->m_saturation = std::round(m_saturation);
};

HSV::HSV(const HSL &hsl) {
  const double lightness = hsl.getLightness() / 100.0,
               saturation = hsl.getSaturation() / 100.0;

  this->m_hue = hsl.getHue();
  this->m_value = (lightness + saturation * std::min(lightness, 1 - lightness));
  this->m_saturation =
      (m_value == 0) ? 0 : (2.0 * (1.0 - lightness / m_value)) * 100.0;

  this->m_value = m_value * 100;
};

double HSV::getHue() const { return this->m_hue; };
double HSV::getSaturation() const { return this->m_saturation; };
double HSV::getValue() const { return this->m_value; };
