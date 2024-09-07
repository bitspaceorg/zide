#include "imgui.h"
#include "utils.h"
#include "app.h"

void render_toolbar(ToolbarState *toolbar_state) {
  const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
  
  ImGui::SetNextWindowPos(ImVec2(0, get_center(200.0f, main_viewport->Size.y)));
  ImGui::SetNextWindowSize(ImVec2(40, 175));  
  
  ImGui::Begin("Toolbar", NULL, WINDOW_FLAGS);

  ImGui::PushFont(gFont); 

  if (ImGui::Selectable("\uf040", toolbar_state->selected_tool == SELECTED_PENCIL,
                        ImGuiSelectableFlags_None, ImVec2(40 - 12, 40))) {
    toolbar_state->selected_tool = SELECTED_PENCIL;
  }
  
  if (ImGui::Selectable("\uf12d", toolbar_state->selected_tool == SELECTED_ERASER,
                        ImGuiSelectableFlags_None, ImVec2(40 - 12, 40))) {
    toolbar_state->selected_tool = SELECTED_ERASER;
  }
  
  if (ImGui::Selectable("\uf1fc", toolbar_state->selected_tool == SELECTED_BUCKET,
                        ImGuiSelectableFlags_None, ImVec2(40 - 12, 40))) {
    toolbar_state->selected_tool = SELECTED_BUCKET;
  }

  ImGui::PopFont();

  ImGui::End();
}

