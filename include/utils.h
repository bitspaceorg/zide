#pragma once

#include "imgui.h"
#include <utility>

inline ImGuiWindowFlags WINDOW_FLAGS =
    0 | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
    ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
    ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBringToFrontOnFocus;


float get_center(float X, float x);
std::pair<ImVec2, ImVec2> get_grid_coordinates(ImVec2 screen_center, int GRID_SIZE, int PIXEL_SIZE, ImVec2 pan_offset);
