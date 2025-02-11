#pragma once

struct HSL;
struct HSV;

struct RGB {
public:
  RGB(double red, double green, double blue, double alpha = 255)
      : m_red(red), m_green(green), m_blue(blue), m_alpha(alpha) {}
  RGB()
      : m_red(0), m_green(0), m_blue(0), m_alpha(0) {}
  explicit RGB(const HSL &hsl);
  explicit RGB(const HSV &hsv);

  double getRed() const;
  double getGreen() const;
  double getBlue() const;
  double getAlpha() const;

private:
  double m_red;
  double m_green;
  double m_blue;
  double m_alpha = 255;
};
