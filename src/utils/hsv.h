#pragma once

struct RGB;
struct HSL;

struct HSV {
public:
  HSV(double hue, double saturation, double value, double alpha = 255)
      : m_hue(hue), m_saturation(saturation), m_value(value){};
  HSV() : m_hue(0), m_saturation(0), m_value(0){};
  explicit HSV(const RGB &rgb);
  explicit HSV(const HSL &hsl);

  double getHue() const;
  double getSaturation() const;
  double getValue() const;

private:
  double m_hue;
  double m_saturation;
  double m_value;
  double m_alpha = 255;
};
