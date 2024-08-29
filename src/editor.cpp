#include "editor.h"

#include "app.h"
#include "imgui.h"
#include "utils.h"
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

/* Init the global vector<vector<PIXEL>> with transperant values
 *
 */
void initialize_grid(int width, int height, EditorState *editor_state) {
  editor_state->CANVAS_WIDTH = width;
  editor_state->CANVAS_HEIGHT = height;
  editor_state->pixel_colors.resize(
      height, std::vector<ImVec4>(width, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)));
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

    auto [grid_top_left_point, grid_bottom_right_point] = get_grid_coordinates(
        screen_center, CANVAS_WIDTH, CANVAS_HEIGHT, PIXEL_SIZE, editor_state->pan_offset);

    draw_transperant_background(CANVAS_WIDTH, CANVAS_HEIGHT, PIXEL_SIZE, grid_top_left_point,
                                draw_list);
    draw_single_frame(grid_top_left_point, editor_state, display_size, draw_list);

    editor_event_listner(editor_state, grid_top_left_point, draw_list);
}

void save_screenshot(EditorState* editor_state){
  const int CANVAS_WIDTH = editor_state->CANVAS_WIDTH;
  const int CANVAS_HEIGHT = editor_state->CANVAS_HEIGHT;

  std::vector<unsigned char> image_data(CANVAS_WIDTH * CANVAS_HEIGHT * 4, 0);

  for(int y = 0; y < CANVAS_HEIGHT; y++){
    for(int x = 0; x < CANVAS_WIDTH; x++){
      ImVec4 color = editor_state->pixel_colors[y][x];
      int index = (y * CANVAS_WIDTH + x) * 4;
      image_data[index + 0] = static_cast<unsigned char>(color.x * 255.0f);
      image_data[index + 1] = static_cast<unsigned char>(color.y * 255.0f);
      image_data[index + 2] = static_cast<unsigned char>(color.z * 255.0f); 
      image_data[index + 3] = static_cast<unsigned char>(color.w * 255.0f); 
    }
  }
  stbi_write_png_compression_level = 0;
  stbi_write_png("zide.png", CANVAS_WIDTH, CANVAS_HEIGHT, 4, image_data.data(), CANVAS_WIDTH * 4);
}

/* Used to render chessboard like thingy for
 * representing transperant background.
 *
 */
static const float TRANSPERANT_BG_PIXEL_SIZE = 8.0;
static void draw_transperant_background(int CANVAS_WIDTH, int CANVAS_HEIGHT, int PIXEL_SIZE,
                                        ImVec2 grid_top_left_point,
                                        ImDrawList *draw_list) {
  float grid_width = CANVAS_WIDTH * PIXEL_SIZE;
  float grid_height = CANVAS_HEIGHT * PIXEL_SIZE;
  float tile_size = std::max(CANVAS_HEIGHT, CANVAS_WIDTH) / TRANSPERANT_BG_PIXEL_SIZE;

  for (float y = 0; y < grid_height; y += tile_size) {
    for (float x = 0; x < grid_width; x += tile_size) {
      ImVec2 pixel_min(grid_top_left_point.x + x, grid_top_left_point.y + y);
      ImVec2 pixel_max(pixel_min.x + tile_size, pixel_min.y + tile_size);

      ImU32 color =
          ((static_cast<int>(x / tile_size) + static_cast<int>(y / tile_size)) % 2 == 0)
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

  int start_x = std::max(0, static_cast<int>(-grid_top_left_point.x / PIXEL_SIZE));
  int start_y = std::max(0, static_cast<int>(-grid_top_left_point.y / PIXEL_SIZE));

  int end_x = std::min(
      CANVAS_WIDTH,
      static_cast<int>((display_size.x - grid_top_left_point.x) / PIXEL_SIZE) + 1);
  int end_y = std::min(
      CANVAS_HEIGHT,
      static_cast<int>((display_size.y - grid_top_left_point.y) / PIXEL_SIZE) + 1);

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

  if(ImGui::IsKeyPressed(ImGuiKey_F2)){
    save_screenshot( editor_state);
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

    if (!is_over_canvas(x, y, editor_state->CANVAS_WIDTH, editor_state->CANVAS_HEIGHT))
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
      if (last_pixel.x >= 0 && last_pixel.x < editor_state->CANVAS_WIDTH &&
          last_pixel.y >= 0 && last_pixel.y < editor_state->CANVAS_HEIGHT) {
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
static bool is_over_canvas(int x, int y, int CANVAS_WIDTH, int CANVAS_HEIGHT) {
  return (x >= 0 && x < CANVAS_WIDTH && y >= 0 && y < CANVAS_HEIGHT);
}
