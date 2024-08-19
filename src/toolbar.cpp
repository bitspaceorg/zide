#include "imgui.h"
#include "utils.h"
#include "app.h"


void render_toolbar(ToolbarState *toolbar_state) {
  const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(ImVec2(0, get_center(250.0f, main_viewport->Size.y)));
  ImGui::SetNextWindowSize(ImVec2(50, 250));

  ImGui::Begin("Toolbar", NULL, WINDOW_FLAGS);

  if (ImGui::Selectable("P", toolbar_state->selected_tool == SELECTED_PENCIL,
                        ImGuiSelectableFlags_None, ImVec2(50 - 16, 50))) {
    toolbar_state->selected_tool = SELECTED_PENCIL;
  }
  if (ImGui::Selectable("E", toolbar_state->selected_tool == SELECTED_ERASER,
                        ImGuiSelectableFlags_None, ImVec2(50 - 16, 50))) {
    toolbar_state->selected_tool = SELECTED_ERASER;
  }
  if (ImGui::Selectable("B", toolbar_state->selected_tool == SELECTED_BUCKET,
                        ImGuiSelectableFlags_None, ImVec2(50 - 16, 50))) {
    toolbar_state->selected_tool = SELECTED_BUCKET;
  }

  ImGui::End();
}
