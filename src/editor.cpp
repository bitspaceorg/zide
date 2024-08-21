#include "editor.h"

#include "app.h"
#include "imgui.h"
#include "utils.h"
#include <vector>

/* Init the global vector<vector<PIXEL>> with transperant values
 *
 */
void initialize_grid(int size, EditorState *editor_state) {
  editor_state->CANVAS_SIZE = size;
  editor_state->pixel_colors.resize(
      size, std::vector<ImVec4>(size, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)));
}

/* HOLDS THE ENTIRE EDITOR CANVAS RENDER LOGIC
 *
 */
void render_grid(EditorState *editor_state) {
  const int CANVAS_SIZE = editor_state->CANVAS_SIZE,
            PIXEL_SIZE = editor_state->PIXEL_SIZE;

  ImDrawList *draw_list = ImGui::GetBackgroundDrawList();
  ImVec2 display_size = ImGui::GetIO().DisplaySize;
  ImVec2 screen_center = {display_size.x * 0.5f, display_size.y * 0.5f};

  auto [grid_top_left_point, grid_bottom_right_point] = get_grid_coordinates(
      screen_center, CANVAS_SIZE, PIXEL_SIZE, editor_state->pan_offset);

  draw_transperant_background(CANVAS_SIZE, PIXEL_SIZE, grid_top_left_point,
                              draw_list);
  draw_single_frame(grid_top_left_point, editor_state, display_size, draw_list);

  editor_event_listner(editor_state, grid_top_left_point, draw_list);
}

/* Used to render chessboard like thingy for
 * representing transperant background.
 *
 */
static const float TRANSPERANT_BG_PIXEL_SIZE = 8.0;
static void draw_transperant_background(int CANVAS_SIZE, int PIXEL_SIZE,
                                        ImVec2 grid_top_left_point,
                                        ImDrawList *draw_list) {
  float grid_size = CANVAS_SIZE * PIXEL_SIZE;
  float tile_size = grid_size / TRANSPERANT_BG_PIXEL_SIZE;

  for (float y = 0; y < grid_size; y += tile_size) {
    for (float x = 0; x < grid_size; x += tile_size) {
      ImVec2 pixel_min(grid_top_left_point.x + x, grid_top_left_point.y + y);
      ImVec2 pixel_max(pixel_min.x + tile_size, pixel_min.y + tile_size);

      ImU32 color =
          ((static_cast<int>(x / tile_size) + static_cast<int>(y / tile_size)) %
               2 ==
           0)
              ? ImColor(200, 200, 200, 255)
              : ImColor(150, 150, 150, 255);

      draw_list->AddRectFilled(pixel_min, pixel_max, color);
    }
  }
}

/* LOOP THROUGH A VEC<VEC<PIXEL>> AND RENDER THEM ON CANVAS.
 * Draws only one frame.
 *
 */
static void draw_single_frame(ImVec2(grid_top_left_point),
                              EditorState *editor_state, ImVec2 display_size,
                              ImDrawList *draw_list) {
  const int PIXEL_SIZE = editor_state->PIXEL_SIZE;
  const int CANVAS_SIZE = editor_state->CANVAS_SIZE;

  int start_x =
      std::max(0, static_cast<int>(-grid_top_left_point.x / PIXEL_SIZE));
  int start_y =
      std::max(0, static_cast<int>(-grid_top_left_point.y / PIXEL_SIZE));

  int end_x = std::min(
      CANVAS_SIZE,
      static_cast<int>((display_size.x - grid_top_left_point.x) / PIXEL_SIZE) +
          1);
  int end_y = std::min(
      CANVAS_SIZE,
      static_cast<int>((display_size.y - grid_top_left_point.y) / PIXEL_SIZE) +
          1);

  for (int y = start_y; y < end_y; y++) {
    for (int x = start_x; x < end_x; x++) {
      ImVec2 pixel_top_left(grid_top_left_point.x + x * PIXEL_SIZE,
                            grid_top_left_point.y + y * PIXEL_SIZE);
      ImVec2 pixel_bottom_right(pixel_top_left.x + PIXEL_SIZE,
                                pixel_top_left.y + PIXEL_SIZE);

      draw_list->AddRectFilled(pixel_top_left, pixel_bottom_right,
                               ImColor(editor_state->pixel_colors[y][x]));
    }
  }
}

/* HANDLER FOR MOUSE MOVEMENT.
 * Can draw and pan.
 */
static ImVec2 editor_event_listner(EditorState *editor_state,
                                   ImVec2 grid_top_left_point,
                                   ImDrawList *draw_list) {
  static ImVec2 last_pixel(-1, -1);
  ImVec2 mouse_position = ImGui::GetMousePos();

  /* PANNING LOGIC
   *
   */
  if (ImGui::IsMouseDragging(ImGuiMouseButton_Middle)) {
    if (!editor_state->is_panning) {
      editor_state->is_panning = true;
      editor_state->last_mouse_pos = mouse_position;
    }
    ImVec2 mouse_difference =
        ImVec2(mouse_position.x - editor_state->last_mouse_pos.x,
               mouse_position.y - editor_state->last_mouse_pos.y);
    editor_state->pan_offset.x += mouse_difference.x;
    editor_state->pan_offset.y += mouse_difference.y;
    editor_state->last_mouse_pos = mouse_position;
  } else {
    editor_state->is_panning = false;
  }

  if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) ||
      ImGui::IsKeyDown(ImGuiKey_RightCtrl)) {
    if (ImGui::IsKeyPressed(ImGuiKey_Equal)) {
      editor_state->PIXEL_SIZE = editor_state->PIXEL_SIZE + 2;
    } else if (ImGui::IsKeyPressed(ImGuiKey_Minus)) {
      editor_state->PIXEL_SIZE = std::max(editor_state->PIXEL_SIZE - 2, 1);
    }
  }

  if (ImGui::GetIO().MouseWheel > 0)
    editor_state->PIXEL_SIZE = editor_state->PIXEL_SIZE + 2;
  else if (ImGui::GetIO().MouseWheel < 0)
    editor_state->PIXEL_SIZE = std::max(editor_state->PIXEL_SIZE - 2, 1);

  if (!ImGui::IsMouseDown(0))
    return last_pixel = ImVec2(-1, -1);

  if (ImGui::IsMouseDown(0)) {
    int x =
        (mouse_position.x - grid_top_left_point.x) / editor_state->PIXEL_SIZE;
    int y =
        (mouse_position.y - grid_top_left_point.y) / editor_state->PIXEL_SIZE;

    if (!is_over_canvas(x, y, editor_state->CANVAS_SIZE))
      return last_pixel = ImVec2(-1, -1);

    if (last_pixel.x == -1 && last_pixel.y == -1)
      return last_pixel = ImVec2(x, y);

    /*
     * THE BELOW LINES FOR MAKING LINE CONTINUES WHEN MOUSE MOVES FAST.
     *
     */
    int pixel_distance_x = abs(x - last_pixel.x);
    int pixel_distance_y = abs(y - last_pixel.y);
    int step_x = last_pixel.x < x ? 1 : -1;
    int step_y = last_pixel.y < y ? 1 : -1;
    int error_accumulator = pixel_distance_x - pixel_distance_y;
    while (true) {
      if (last_pixel.x >= 0 && last_pixel.x < editor_state->CANVAS_SIZE &&
          last_pixel.y >= 0 && last_pixel.y < editor_state->CANVAS_SIZE) {
        editor_state->pixel_colors[last_pixel.y][last_pixel.x] =
            ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
        ImVec2 pixelMin(
            grid_top_left_point.x + last_pixel.x * editor_state->PIXEL_SIZE,
            grid_top_left_point.y + last_pixel.y * editor_state->PIXEL_SIZE);
        ImVec2 pixelMax(pixelMin.x + editor_state->PIXEL_SIZE,
                        pixelMin.y + editor_state->PIXEL_SIZE);
        draw_list->AddRectFilled(
            pixelMin, pixelMax,
            ImColor(editor_state->pixel_colors[last_pixel.y][last_pixel.x]));
      }

      if (last_pixel.x == x && last_pixel.y == y)
        break;

      int errorDouble = 2 * error_accumulator;
      if (errorDouble > -pixel_distance_y) {
        error_accumulator -= pixel_distance_y;
        last_pixel.x += step_x;
      }
      if (errorDouble < pixel_distance_x) {
        error_accumulator += pixel_distance_x;
        last_pixel.y += step_y;
      }
    }
  }

  return ImVec2();
}

/* TO CHECK WEATHER MOUSE IS ABOVE THE CANVAS
 *
 */
static bool is_over_canvas(int x, int y, int CANVAS_SIZE) {
  return (x >= 0 && x < CANVAS_SIZE && y >= 0 && y < CANVAS_SIZE);
};
