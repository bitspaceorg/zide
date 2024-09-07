#include "editor.h"
#include "imgui.h"
#include "utils.h"
#include "app.h"
#include "init.h"
#include <string>

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
    	if (ImGui::BeginMenu("Import")) {
      	if (ImGui::MenuItem("Color palete", "CTRL+SHIFT+C")) {
					std::string contents = open_file_dialog_return_contents_gpl();
					if(contents.size()>1){
						parse_gpl_file(contents, app_state.color_swatch_state);
					}
      	}
				ImGui::EndMenu();
      }
      ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Edit")) {
      if (ImGui::MenuItem("Undo", "CTRL+Z")) {
      }
      if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {
      }
      if (ImGui::MenuItem("Change Dimensions", "")) {
        app_state.editor_state.changing_dimensions = true;
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
  if (app_state.editor_state.changing_dimensions) {
    render_dimensions_select();
  }
}
