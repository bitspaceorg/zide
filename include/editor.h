#pragma once

#include "app.h"

void initialize_grid(int size, EditorState *editor_state);
void render_grid(EditorState *editor_state);
static void draw_transperant_background(int GRID_SIZE, int PIXEL_SIZE, ImVec2 grid_top_left_point, ImDrawList *draw_list);
static void draw_single_frame(ImVec2 grid_top_left_point, EditorState *editor_state, ImVec2 display_size, ImDrawList *draw_list);
static ImVec2 editor_event_listner(EditorState* editor_state, ImVec2 grid_top_left_point, ImDrawList* draw_list);
static bool is_over_canvas(int x, int y, int CANVAS_SIZE);
