#include "utils.h"
#include "imgui.h"

float get_center(float x, float X) {
  float center_X = X / 2;
  float center_x = x / 2;

  return center_X - center_x;
};

ImGuiWindowFlags window_flags =
    0 | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
    ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
    ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBringToFrontOnFocus;
