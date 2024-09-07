#pragma once

#include "imgui.h"
#include <array>
#include <atomic>
#include <unordered_map>
#include <stack>
#include <vector>

#include "colorswatch.h"

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
  int fps = 2;
  int active_frame = 0;
  int total_frames = 1;
  std::atomic<bool> is_animating;
};

/* HOLD UP */

enum ACTION { StrokeAction, AddFrameAction, DeleteFrameAction };

struct ArrayHash {
    std::size_t operator()(const std::array<int, 3>& arr) const {
        std::size_t hash = 0;
        for (int i : arr) {
            hash ^= std::hash<int>()(i) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
        }
        return hash;
    }
};

struct UndoRedoState {
  std::stack<std::unordered_map<std::array<int, 3>, ImVec4, ArrayHash>> stroke_undo_stack,
      stroke_redo_stack;
  std::unordered_map<std::array<int, 3>, ImVec4, ArrayHash> undo_temp, redo_temp;

  std::stack<int> undo_action_stack;
  std::stack<int> redo_action_stack;
};

/* LET ME COOK */
const int MIN_PIXEL_SIZE = 1;
const int MAX_PIXEL_SIZE = 70;
/* EDITOR STATE
 */
struct EditorState {
  int CANVAS_WIDTH = 0;
  int CANVAS_HEIGHT = 0;
  int PIXEL_SIZE = 10;
  ImVec2 pan_offset = ImVec2(0, 0);
  ImVec2 last_mouse_pos = ImVec2(0, 0);

  bool is_panning = false;
  bool changing_dimensions = false;

  float pan_speed = 10.0f;
  std::vector<std::vector<std::vector<ImVec4>>> pixel_colors;
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
  ColorSwatchState color_swatch_state = {
		.pallet = {
      Color{.name = "Color1", .r = 226.0f / 255.0f, .g = 228.0f / 255.0f, .b = 223.0f / 255.0f, .a = 1.0f}, // e2e4df
      Color{.name = "Color2", .r = 197.0f / 255.0f, .g = 207.0f / 255.0f, .b = 196.0f / 255.0f, .a = 1.0f}, // c5cfc4
      Color{.name = "Color3", .r = 168.0f / 255.0f, .g = 181.0f / 255.0f, .b = 174.0f / 255.0f, .a = 1.0f}, // a8b5ae
      Color{.name = "Color4", .r = 146.0f / 255.0f, .g = 146.0f / 255.0f, .b = 156.0f / 255.0f, .a = 1.0f}, // 92929c
      Color{.name = "Color5", .r = 255.0f / 255.0f, .g = 236.0f / 255.0f, .b = 237.0f / 255.0f, .a = 1.0f}, // ffeced
      Color{.name = "Color6", .r = 251.0f / 255.0f, .g = 212.0f / 255.0f, .b = 210.0f / 255.0f, .a = 1.0f}, // fbd4d2
      Color{.name = "Color7", .r = 241.0f / 255.0f, .g = 180.0f / 255.0f, .b = 180.0f / 255.0f, .a = 1.0f}, // f1b4b4
      Color{.name = "Color8", .r = 204.0f / 255.0f, .g = 163.0f / 255.0f, .b = 163.0f / 255.0f, .a = 1.0f}, // cca3a3
      Color{.name = "Color9", .r = 241.0f / 255.0f, .g = 234.0f / 255.0f, .b = 182.0f / 255.0f, .a = 1.0f}, // f1eab6
      Color{.name = "Color10", .r = 228.0f / 255.0f, .g = 219.0f / 255.0f, .b = 160.0f / 255.0f, .a = 1.0f}, // e4dba0
      Color{.name = "Color11", .r = 202.0f / 255.0f, .g = 193.0f / 255.0f, .b = 138.0f / 255.0f, .a = 1.0f}, // cac18a
      Color{.name = "Color12", .r = 171.0f / 255.0f, .g = 164.0f / 255.0f, .b = 123.0f / 255.0f, .a = 1.0f}  // aba47b
    },
    .current_active = 0
	};
  EditorState editor_state;
  UndoRedoState undo_redo_state;
};
extern AppState app_state;
extern ImFont* gFont;

void run_application();
void initialize_application();
void LoadFonts();
// static void render_toolbar(ToolbarState *toolbar_state);
// static void render_main_menu_bar();
// static void render_timeline();
// static void render_color_swatch();
//
// static void initialize_grid(int size, EditorState *editor_state);
// static void reg[der_grid(EditorState *editor_state);
