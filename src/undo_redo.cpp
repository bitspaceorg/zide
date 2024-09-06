#include "app.h"
#include "array"
#include "imgui.h"
#include "unordered_map"

void undo() {
  if (app_state.undo_redo_state.stroke_undo_stack.empty())
    return;
  std::unordered_map<std::array<int, 3>, ImVec4, ArrayHash> top =
      app_state.undo_redo_state.stroke_undo_stack.top();

  app_state.undo_redo_state.stroke_undo_stack.pop();

  for (auto &[k, v] : top) {
    app_state.undo_redo_state.redo_temp[{k[0], k[1], k[2]}] =
        app_state.editor_state.pixel_colors[k[0]][k[1]][k[2]];
    app_state.editor_state.pixel_colors[k[0]][k[1]][k[2]] = v;
  }

  app_state.undo_redo_state.stroke_redo_stack.push(
      app_state.undo_redo_state.redo_temp);
  app_state.undo_redo_state.redo_temp.clear();
}

void redo() {
  if (app_state.undo_redo_state.stroke_redo_stack.empty())
    return;

  std::unordered_map<std::array<int, 3>, ImVec4, ArrayHash> top =
      app_state.undo_redo_state.stroke_redo_stack.top();

  app_state.undo_redo_state.stroke_redo_stack.pop();

  for (auto &[k, v] : top) {
    app_state.undo_redo_state.undo_temp[{k[0], k[1], k[2]}] =
        app_state.editor_state.pixel_colors[k[0]][k[1]][k[2]];
    app_state.editor_state.pixel_colors[k[0]][k[1]][k[2]] = v;
  }
  app_state.undo_redo_state.stroke_undo_stack.push(
      app_state.undo_redo_state.undo_temp);
  app_state.undo_redo_state.undo_temp.clear();
}
