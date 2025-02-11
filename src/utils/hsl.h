#pragma once

struct RGB;
struct HSV;

struct HSL {
public:
  HSL(double hue, double saturation, double lightness, double alpha = 255)
      : m_hue(hue), m_saturation(saturation), m_lightness(lightness){};
  HSL() : m_hue(0), m_saturation(0), m_lightness(0){};
  explicit HSL(const RGB &rgb);
  explicit HSL(const HSV &hsv);

  double getHue() const;
  double getSaturation() const;
  double getLightness() const;

private:
  double m_hue;
  double m_saturation;
  double m_lightness;
  double m_alpha = 255;
};
