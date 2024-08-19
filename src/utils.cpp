#include "utils.h"
#include "imgui.h"
#include <utility>

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
std::pair<ImVec2, ImVec2> get_grid_coordinates(ImVec2 screen_center, int CANVAS_SIZE, int PIXEL_SIZE, ImVec2 pan_offset) {
  ImVec2 grid_top_left_point(
      screen_center.x - (1.0 * CANVAS_SIZE * PIXEL_SIZE / 2) + pan_offset.x,
      screen_center.y - (1.0 * CANVAS_SIZE * PIXEL_SIZE / 2) + pan_offset.y);

  ImVec2 grid_bottom_right_point(
      screen_center.x + (1.0 * CANVAS_SIZE * PIXEL_SIZE / 2) + pan_offset.x,
      screen_center.y + (1.0 * CANVAS_SIZE * PIXEL_SIZE / 2) + pan_offset.y);

  return std::make_pair(grid_top_left_point, grid_bottom_right_point);
}


