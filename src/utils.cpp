#include "utils.h"
#include "imgui.h"
#include "colorswatch.h"
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <nfd.h>

float get_center(float x, float X) {
  float center_X = X / 2;
  float center_x = x / 2;

  return center_X - center_x;
};

/* gets the top-left and bottom-right co-ordinates 
 * of the canvas, and return them as pair.
 *  .-------
 *  |      |
 *  |      |
 *  |      |
 *  |      |
 *  -------. -> points
*/
std::pair<ImVec2, ImVec2> get_grid_coordinates(ImVec2 screen_center, int CANVAS_WIDTH, int CANVAS_HEIGHT, int PIXEL_SIZE, ImVec2 pan_offset) {
  ImVec2 grid_top_left_point(
      screen_center.x - (1.0 * CANVAS_WIDTH * PIXEL_SIZE / 2) + pan_offset.x,
      screen_center.y - (1.0 * CANVAS_HEIGHT * PIXEL_SIZE / 2) + pan_offset.y);
  ImVec2 grid_bottom_right_point(
      screen_center.x + (1.0 * CANVAS_WIDTH * PIXEL_SIZE / 2) + pan_offset.x,
      screen_center.y + (1.0 * CANVAS_HEIGHT * PIXEL_SIZE / 2) + pan_offset.y);

  return std::make_pair(grid_top_left_point, grid_bottom_right_point);
}

std::string open_file_dialog_return_contents_gpl() {
  nfdchar_t *outPath = NULL;
  nfdresult_t result = NFD_OpenDialog("gpl", NULL, &outPath);
  if(result == NFD_OKAY) {
    std::ifstream file(outPath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    free(outPath);
    return buffer.str();
  } else if(result == NFD_CANCEL) {
    return "";
  } else {
    std::cerr << "Error: " << NFD_GetError() << std::endl;
    return "";
  }
}


bool parse_gpl_file(std::string& file_contents, ColorSwatchState& color_swatch_state) {
	std::istringstream file(file_contents);
	std::string line;
	color_swatch_state.pallet.clear();
	std::getline(file, line);
	std::getline(file, line);
	while (std::getline(file, line)) {
  	std::istringstream iss(line);
  	int r, g, b;
		std::string name;
    if (iss >> r >> g >> b) {
    	std::getline(iss >> std::ws, name);
      color_swatch_state.pallet.push_back(Color{
      	.name = name,
        .r = r / 255.0f,
        .g = g / 255.0f,
        .b = b / 255.0f,
        .a = 1.0f
      });
    }
  }
	if (!color_swatch_state.pallet.empty()) {
  	color_swatch_state.current_active = 0;
	}
	return !color_swatch_state.pallet.empty();
}

