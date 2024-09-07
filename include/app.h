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
const int MAX_PIXEL_SIZE = 10;
/* EDITOR STATE
 */
struct EditorState {
  int CANVAS_WIDTH = 512;
  int CANVAS_HEIGHT = 512;
  int PIXEL_SIZE = 10;
  ImVec2 pan_offset = ImVec2(0, 0);
  ImVec2 last_mouse_pos = ImVec2(0, 0);
  bool is_panning = false;
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
      Color{.name = "Black", .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f},
      Color{.name = "Red", .r = 1.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f},
      Color{.name = "Green", .r = 0.0f, .g = 1.0f, .b = 0.0f, .a = 1.0f}
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
