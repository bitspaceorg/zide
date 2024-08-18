#include "app.h"
#include "imgui.h"
#include "theme.h"
#include "utils.h"
#include <cstdlib>

ImGuiWindowFlags WINDOWS_FLAG =
    ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
    ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoNav |
    ImGuiWindowFlags_NoBringToFrontOnFocus;

void initialize_application() { apply_style(); }

AppState app_state;
void run_application() {
  render_main_menu_bar();
  if (app_state.is_timeline_visible) {
    render_timeline();
  }
  if (app_state.is_toolbar_visible) {
    render_toolbar(&app_state.toolbar_state);
  }
  if (app_state.is_colorswatch_visible) {
    render_color_swatch();
  }
};

static void render_toolbar(ToolbarState *toolbar_state) {
  const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(ImVec2(0, get_center(250.0f, main_viewport->Size.y)));
  ImGui::SetNextWindowSize(ImVec2(50, 250));

  ImGui::Begin("Toolbar", NULL, WINDOWS_FLAG);

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

static void render_main_menu_bar() {
  if (ImGui::BeginMainMenuBar()) {
    if (ImGui::BeginMenu("File")) {
      if (ImGui::MenuItem("New", "CTRL+N")) {
      }
      if (ImGui::MenuItem("Open", "CTRL+O")) {
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

static void help_marker(const char *desc) {
  ImGui::TextDisabled("(?)");
  if (ImGui::BeginItemTooltip()) {
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(desc);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}

static void render_timeline() {

  const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(ImVec2(get_center(700.0f, main_viewport->Size.x),
                                 main_viewport->Size.y - 100));
  ImGui::SetNextWindowSize(ImVec2(700, 100));

  ImGui::Begin("Tiemline", NULL, WINDOWS_FLAG);
  ImGui::End();
}

static void render_color_swatch() {
  const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(ImVec2(main_viewport->Size.x - 250,
                                 get_center(250.0f, main_viewport->Size.y)));
  ImGui::SetNextWindowSize(ImVec2(250, 250));

  ImGui::Begin("Color Swatch", NULL, WINDOWS_FLAG);
  ImGui::End();
}
