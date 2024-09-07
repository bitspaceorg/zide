#include "editor.h"
#include "app.h"
#include "imgui.h"
#include "utils.h"
#include <array>
#include <queue>
#include <vector>
#include <algorithm>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

/* Init the global vector<vector<PIXEL>> with transperant values
 *
 */
void initialize_grid(int width, int height, EditorState *editor_state) {
  editor_state->CANVAS_WIDTH = width;
  editor_state->CANVAS_HEIGHT = height;
  editor_state->pixel_colors.resize(
      1,
      std::vector<std::vector<ImVec4>>(
          height, std::vector<ImVec4>(width, ImVec4(0.0f, 0.0f, 0.0f, 0.0f))));
}

void add_frame(int width, int height, EditorState *editor_state) {
  app_state.timeline_state.total_frames += 1;
  editor_state->pixel_colors.resize(
      app_state.timeline_state.total_frames,
      std::vector<std::vector<ImVec4>>(
          height, std::vector<ImVec4>(width, ImVec4(0.0f, 0.0f, 0.0f, 0.0f))));
  app_state.timeline_state.active_frame =
      app_state.timeline_state.total_frames - 1;
}

/* HOLDS THE ENTIRE EDITOR CANVAS RENDER LOGIC
 *
 */
void render_grid(EditorState *editor_state) {
  const int CANVAS_WIDTH = editor_state->CANVAS_WIDTH,
            CANVAS_HEIGHT = editor_state->CANVAS_HEIGHT,
            PIXEL_SIZE = editor_state->PIXEL_SIZE;

  ImDrawList *draw_list = ImGui::GetBackgroundDrawList();
  ImVec2 display_size = ImGui::GetIO().DisplaySize;
  ImVec2 screen_center = {display_size.x * 0.5f, display_size.y * 0.5f};

  auto [grid_top_left_point, grid_bottom_right_point] =
      get_grid_coordinates(screen_center, CANVAS_WIDTH, CANVAS_HEIGHT,
                           PIXEL_SIZE, editor_state->pan_offset);

  draw_transperant_background(CANVAS_WIDTH, CANVAS_HEIGHT, PIXEL_SIZE,
                              grid_top_left_point, draw_list);
  draw_single_frame(grid_top_left_point, editor_state, display_size, draw_list);

  editor_event_listner(editor_state, grid_top_left_point, draw_list);
}

/* EXPORT LOGIC
 *
 */
void save_screenshot(EditorState *editor_state) {
  const int CANVAS_WIDTH = editor_state->CANVAS_WIDTH;
  const int CANVAS_HEIGHT = editor_state->CANVAS_HEIGHT;

  std::vector<unsigned char> image_data(app_state.timeline_state.total_frames *
                                            CANVAS_WIDTH * CANVAS_HEIGHT * 4,
                                        0);

  for (int z = 0; z < app_state.timeline_state.total_frames; z++) {
    for (int y = 0; y < CANVAS_HEIGHT; y++) {
      for (int x = 0; x < CANVAS_WIDTH; x++) {
        ImVec4 color = editor_state->pixel_colors[z][y][x];
        int index = (y * CANVAS_WIDTH + x) * 4;
        image_data[index + 0] = static_cast<unsigned char>(color.x * 255.0f);
        image_data[index + 1] = static_cast<unsigned char>(color.y * 255.0f);
        image_data[index + 2] = static_cast<unsigned char>(color.z * 255.0f);
        image_data[index + 3] = static_cast<unsigned char>(color.w * 255.0f);
      }
    }
  }
  stbi_write_png_compression_level = 0;
  stbi_write_png("zide.png",
                 CANVAS_WIDTH * app_state.timeline_state.total_frames,
                 CANVAS_HEIGHT, 4, image_data.data(), CANVAS_WIDTH * 4);
}

/* Used to render chessboard like thingy for
 * representing transperant background.
 *
 */
static const float TRANSPERANT_BG_PIXEL_SIZE = 8.0;
static void draw_transperant_background(int CANVAS_WIDTH, int CANVAS_HEIGHT,
                                        int PIXEL_SIZE,
                                        ImVec2 grid_top_left_point,
                                        ImDrawList *draw_list) {
  float grid_width = CANVAS_WIDTH * PIXEL_SIZE;
  float grid_height = CANVAS_HEIGHT * PIXEL_SIZE;
  float tile_size =
      std::max(CANVAS_HEIGHT, CANVAS_WIDTH) / TRANSPERANT_BG_PIXEL_SIZE;

  for (float y = 0; y < grid_height; y += tile_size) {
    for (float x = 0; x < grid_width; x += tile_size) {
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
static void draw_single_frame(ImVec2 grid_top_left_point,
                              EditorState *editor_state, ImVec2 display_size,
                              ImDrawList *draw_list) {
  const int PIXEL_SIZE = editor_state->PIXEL_SIZE;
  const int CANVAS_WIDTH = editor_state->CANVAS_WIDTH;
  const int CANVAS_HEIGHT = editor_state->CANVAS_HEIGHT;

  int start_x =
      std::max(0, static_cast<int>(-grid_top_left_point.x / PIXEL_SIZE));
  int start_y =
      std::max(0, static_cast<int>(-grid_top_left_point.y / PIXEL_SIZE));

  int end_x = std::min(
      CANVAS_WIDTH,
      static_cast<int>((display_size.x - grid_top_left_point.x) / PIXEL_SIZE) +
          1);
  int end_y = std::min(
      CANVAS_HEIGHT,
      static_cast<int>((display_size.y - grid_top_left_point.y) / PIXEL_SIZE) +
          1);

  for (int y = start_y; y < end_y; y++) {
    for (int x = start_x; x < end_x; x++) {
      ImVec2 pixel_top_left(grid_top_left_point.x + x * PIXEL_SIZE,
                            grid_top_left_point.y + y * PIXEL_SIZE);
      ImVec2 pixel_bottom_right(pixel_top_left.x + PIXEL_SIZE,
                                pixel_top_left.y + PIXEL_SIZE);

      draw_list->AddRectFilled(
          pixel_top_left, pixel_bottom_right,
          ImColor(
              editor_state
                  ->pixel_colors[app_state.timeline_state.active_frame][y][x]));
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

  if (ImGui::IsAnyItemHovered() || ImGui::IsWindowHovered(ImGuiHoveredFlags_AnyWindow)) {
    return ImVec2();
  }
  /* SCREENSHOT KEYBIND
   *
   */
  if (ImGui::IsKeyPressed(ImGuiKey_F2)) {
    save_screenshot(editor_state);
  }

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

  /* ZOOMING LOGIC
   *
   */
  if (ImGui::IsKeyDown(ImGuiKey_LeftCtrl) ||
      ImGui::IsKeyDown(ImGuiKey_RightCtrl)) {
    if (ImGui::IsKeyPressed(ImGuiKey_Equal)) {
      editor_state->PIXEL_SIZE = std::min(editor_state->PIXEL_SIZE + 1, MAX_PIXEL_SIZE);
    } else if (ImGui::IsKeyPressed(ImGuiKey_Minus)) {
      editor_state->PIXEL_SIZE = std::max(editor_state->PIXEL_SIZE - 1, MIN_PIXEL_SIZE);
    }
  }

  if (ImGui::GetIO().MouseWheel > 0)
    editor_state->PIXEL_SIZE = std::min(editor_state->PIXEL_SIZE + 1, MAX_PIXEL_SIZE);
  else if (ImGui::GetIO().MouseWheel < 0)
    editor_state->PIXEL_SIZE = std::max(editor_state->PIXEL_SIZE - 1, MIN_PIXEL_SIZE);

  /* DRAWING LOGIC
   *
   */
  if (!ImGui::IsMouseDown(0)) {
    if (!app_state.undo_redo_state.undo_temp.empty()) {
      app_state.undo_redo_state.stroke_undo_stack.push(
          app_state.undo_redo_state.undo_temp);
      app_state.undo_redo_state.undo_temp.clear();
      while (!app_state.undo_redo_state.stroke_redo_stack.empty())
        app_state.undo_redo_state.stroke_redo_stack.pop();
    }
    return last_pixel = ImVec2(-1, -1);
  }

  if (ImGui::IsKeyPressed(ImGuiKey_MouseLeft) &&
      (app_state.toolbar_state.selected_tool == SELECTED_BUCKET)) {
    int x =
        (mouse_position.x - grid_top_left_point.x) / editor_state->PIXEL_SIZE;
    int y =
        (mouse_position.y - grid_top_left_point.y) / editor_state->PIXEL_SIZE;

    if (!is_over_canvas(x, y, editor_state->CANVAS_WIDTH,
                        editor_state->CANVAS_HEIGHT))
      return last_pixel = ImVec2(-1, -1);
    fill_bucket(editor_state, draw_list, grid_top_left_point, x, y);
  }

  if (ImGui::IsMouseDown(0) &&
      !(app_state.toolbar_state.selected_tool == SELECTED_BUCKET)) {
    int x =
        (mouse_position.x - grid_top_left_point.x) / editor_state->PIXEL_SIZE;
    int y =
        (mouse_position.y - grid_top_left_point.y) / editor_state->PIXEL_SIZE;

    if (!is_over_canvas(x, y, editor_state->CANVAS_WIDTH,
                        editor_state->CANVAS_HEIGHT))
      return last_pixel = ImVec2(-1, -1);

    if (last_pixel.x == -1 && last_pixel.y == -1)
      last_pixel = ImVec2(x, y);

    /*
     * THE BELOW LINES FOR MAKING LINE CONTINUES WHEN MOUSE MOVES FAST.
     *
     */
    draw_and_erase(editor_state, last_pixel, ImVec2(x, y), grid_top_left_point,
                   draw_list);
    last_pixel = ImVec2(x, y);
  }

  return ImVec2();
}

/* TO CHECK WEATHER MOUSE IS ABOVE THE CANVAS
 *
 */
static bool is_over_canvas(int x, int y, int CANVAS_WIDTH, int CANVAS_HEIGHT) {
  return (x >= 0 && x < CANVAS_WIDTH && y >= 0 && y < CANVAS_HEIGHT);
}

/* DRAW AND ERASE
 *
 */
static void draw_and_erase(EditorState *editor_state, ImVec2 start, ImVec2 end,
                           ImVec2 grid_top_left_point, ImDrawList *draw_list) {
  int x = static_cast<int>(end.x);
  int y = static_cast<int>(end.y);
  ImVec2 last_pixel = start;

  int pixel_distance_x = abs(x - static_cast<int>(last_pixel.x));
  int pixel_distance_y = abs(y - static_cast<int>(last_pixel.y));
  int step_x = last_pixel.x < x ? 1 : -1;
  int step_y = last_pixel.y < y ? 1 : -1;
  int error_accumulator = pixel_distance_x - pixel_distance_y;
  auto [name, r, g, b, a] =
      app_state.color_swatch_state
          .pallet[app_state.color_swatch_state.current_active];

  int ux = static_cast<int>(last_pixel.x);
  int uy = static_cast<int>(last_pixel.y);

  while (true) {
    if (last_pixel.x >= 0 && last_pixel.x < editor_state->CANVAS_WIDTH &&
        last_pixel.y >= 0 && last_pixel.y < editor_state->CANVAS_HEIGHT) {
      int ux = static_cast<int>(last_pixel.x);
      int uy = static_cast<int>(last_pixel.y);

      ImVec4 prev_color =
          editor_state
              ->pixel_colors[app_state.timeline_state.active_frame][uy][ux];

      if (app_state.undo_redo_state.undo_temp.find(
              {app_state.timeline_state.active_frame, uy, ux}) ==
          app_state.undo_redo_state.undo_temp.end())
        app_state.undo_redo_state
            .undo_temp[{app_state.timeline_state.active_frame, uy, ux}] =
            prev_color;

      if (app_state.toolbar_state.selected_tool == SELECTED_ERASER)
        editor_state->pixel_colors[app_state.timeline_state.active_frame]
                                  [static_cast<int>(last_pixel.y)]
                                  [static_cast<int>(last_pixel.x)] =
            ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
      else if (app_state.toolbar_state.selected_tool == SELECTED_PENCIL)
        editor_state->pixel_colors[app_state.timeline_state.active_frame]
                                  [static_cast<int>(last_pixel.y)]
                                  [static_cast<int>(last_pixel.x)] =
            ImVec4(r, g, b, a);

      ImVec2 pixelMin(
          grid_top_left_point.x + last_pixel.x * editor_state->PIXEL_SIZE,
          grid_top_left_point.y + last_pixel.y * editor_state->PIXEL_SIZE);
      ImVec2 pixelMax(pixelMin.x + editor_state->PIXEL_SIZE,
                      pixelMin.y + editor_state->PIXEL_SIZE);
      draw_list->AddRectFilled(
          pixelMin, pixelMax,
          ImColor(
              editor_state->pixel_colors[app_state.timeline_state.active_frame]
                                        [static_cast<int>(last_pixel.y)]
                                        [static_cast<int>(last_pixel.x)]));
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

/* BUCKET FILL LOGIC
 *
 */
static void fill_bucket(EditorState *editor_state, ImDrawList *draw_list,
                        ImVec2 grid_top_left_point, int start_x, int start_y) {
  const int HEIGHT = editor_state->CANVAS_HEIGHT;
  const int WIDTH = editor_state->CANVAS_WIDTH;
  std::queue<std::pair<int, int>> q;
  std::vector<std::vector<int>> visited(HEIGHT, std::vector<int>(WIDTH, 0));

  auto [name, r, g, b, a] =
      app_state.color_swatch_state
          .pallet[app_state.color_swatch_state.current_active];
  ImVec4 original =
      editor_state->pixel_colors[app_state.timeline_state.active_frame][start_y]
                                [start_x];

  if (original.x == r && original.y == g && original.z == b && original.w == a)
    return;
  q.push({start_x, start_y});
  visited[start_y][start_x] = true;
  const int dx[] = {0, 1, 0, -1};
  const int dy[] = {-1, 0, 1, 0};

  std::unordered_map<std::array<int, 3>, ImVec4, ArrayHash> mp;

  while (!q.empty()) {
    int x = q.front().first;
    int y = q.front().second;
    q.pop();

    mp[{app_state.timeline_state.active_frame, y, x}] =
        editor_state->pixel_colors[app_state.timeline_state.active_frame][y][x];

    editor_state->pixel_colors[app_state.timeline_state.active_frame][y][x] =
        ImVec4(r, g, b, a);

    ImVec2 pixelMin(grid_top_left_point.x + x * editor_state->PIXEL_SIZE,
                    grid_top_left_point.y + y * editor_state->PIXEL_SIZE);
    ImVec2 pixelMax(pixelMin.x + editor_state->PIXEL_SIZE,
                    pixelMin.y + editor_state->PIXEL_SIZE);
    draw_list->AddRectFilled(
        pixelMin, pixelMax,
        ImColor(
            editor_state
                ->pixel_colors[app_state.timeline_state.active_frame][y][x]));

    for (int i = 0; i < 4; ++i) {
      int new_x = x + dx[i];
      int new_y = y + dy[i];

      if (new_x >= 0 && new_x < WIDTH && new_y >= 0 && new_y < HEIGHT &&
          !visited[new_y][new_x]) {
        ImVec4 color =
            editor_state->pixel_colors[app_state.timeline_state.active_frame]
                                      [new_y][new_x];
        if (!(color.x == original.x && color.y == original.y &&
              color.z == original.z && color.w == original.w))
          continue;
        q.push({new_x, new_y});
        visited[new_y][new_x] = 1;
      }
    }
  }
  if (!mp.empty()) {
    app_state.undo_redo_state.stroke_undo_stack.push(mp);
    mp.clear();
  }
}
