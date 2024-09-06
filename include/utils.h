#pragma once

#include "imgui.h"
#include <utility>
#include <string>
#include "colorswatch.h"

inline ImGuiWindowFlags WINDOW_FLAGS =
    0 | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
    ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
    ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBringToFrontOnFocus;


std::string open_file_dialog_return_contents_gpl();
bool parse_gpl_file(std::string& file_contents, ColorSwatchState& color_swatch_state);

float get_center(float X, float x);
std::pair<ImVec2, ImVec2> get_grid_coordinates(ImVec2 screen_center, int CANVAS_WIDTH, int CANVAS_HEIGHT, int PIXEL_SIZE, ImVec2 pan_offset);
