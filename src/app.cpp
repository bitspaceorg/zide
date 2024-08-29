#include "app.h"
#include "editor.h"
#include "imgui.h"
#include "menubar.h"
#include "theme.h"
#include "timeline.h"
#include "colorswatch.h"
#include "toolbar.h"

AppState app_state;

void initialize_application() {
  apply_style();
  initialize_grid(app_state.editor_state.CANVAS_WIDTH, app_state.editor_state.CANVAS_HEIGHT, &app_state.editor_state);
}

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
  render_grid(&app_state.editor_state);
};

static void help_marker(const char *desc) {
  ImGui::TextDisabled("(?)");
  if (ImGui::BeginItemTooltip()) {
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(desc);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();
  }
}
