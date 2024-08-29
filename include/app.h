#pragma once

#include "imgui.h"
#include <string>
#include <vector>
#include "imgui.h"

/*  TOOLBAR STATE
 *
 */
enum SelectedTool { SELECTED_PENCIL, SELECTED_ERASER, SELECTED_BUCKET };
struct ToolbarState {
  SelectedTool selected_tool = SELECTED_PENCIL;
  int pencil_size = 10;
  int eraser_size = 10;
};

/* TIMELINE STATE
 *
 */
struct TimelineState {
  int fps = 24;
  int total_frames = 1;
  int current_seekhead = 0;
};

/* COLOR SWATCH STATE
 *
 */
struct Color {
  std::string name;
  float r, g, b, a;
};
struct ColorSwatchState {
  std::vector<Color> pallet{
      Color{.name = "black", .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f},
      Color{.name = "white", .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f},
      Color{.name = "red", .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f}};
  int current_active = 0;
};

/* EDITOR STATE
 */
struct EditorState {
  int CANVAS_SIZE = 512;
  int CANVAS_WIDTH = 32;
  int CANVAS_HEIGHT = 64;
  int PIXEL_SIZE = 10;
  ImVec2 pan_offset = ImVec2(0, 0);
  ImVec2 last_mouse_pos = ImVec2(0, 0);
  bool is_panning = false;
  float pan_speed = 10.0f;
  std::vector<std::vector<ImVec4>> pixel_colors;
};

/* GLOBAL APP STATE
 *
 *
 */
struct AppState {
  bool is_timeline_visible = true;
  bool is_toolbar_visible = true;
  bool is_colorswatch_visible = true;

  ToolbarState toolbar_state;
  TimelineState timeline_state;
  ColorSwatchState color_swatch_state;
  EditorState editor_state;
};
extern AppState app_state;

void run_application();
void initialize_application();
// static void render_toolbar(ToolbarState *toolbar_state);
// static void render_main_menu_bar();
// static void render_timeline();
// static void render_color_swatch();
//
// static void initialize_grid(int size, EditorState *editor_state);
// static void render_grid(EditorState *editor_state);
