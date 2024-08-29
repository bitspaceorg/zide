#include "editor.h"
#include "imgui.h"
#include "app.h"

void render_main_menu_bar() {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("New", "CTRL+N")) {
      }
      if (ImGui::MenuItem("Open", "CTRL+O")) {
      }
      if (ImGui::MenuItem("Export", "F2")) {
        save_screenshot(&app_state.editor_state);
      }
      ImGui::Separator();
      if (ImGui::MenuItem("Exit", "CTRL+X")) {
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit")) {
      if (ImGui::MenuItem("Undo", "CTRL+Z")) {
      }
      if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Windows")) {
      if (ImGui::MenuItem("Timeline", NULL, &app_state.is_timeline_visible)) {
      }
      if (ImGui::MenuItem("Toolbar", NULL, &app_state.is_toolbar_visible)) {
      }
      if (ImGui::MenuItem("ColorSwatch", NULL,
                          &app_state.is_colorswatch_visible)) {
      }
      ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();
  }
}
