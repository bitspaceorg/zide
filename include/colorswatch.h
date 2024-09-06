#pragma once

#include <vector>
#include <string>

struct Color {
  std::string name;
  float r, g, b, a;
};
struct ColorSwatchState {
  std::vector<Color> pallet;
  int current_active;
};

void render_color_swatch();
