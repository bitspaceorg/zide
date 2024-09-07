#include "app.h"
#include "colorswatch.h"
#include "editor.h"
#include "imgui.h"
#include "menubar.h"
#include "theme.h"
#include "timeline.h"
#include "toolbar.h"
#include "init.h"
#include "../fonts/embedded_font.inc"

AppState app_state;
ImFont* gFont = nullptr;

void LoadFonts() {
  ImGuiIO &io = ImGui::GetIO();

  gFont = io.Fonts->AddFontFromMemoryCompressedBase85TTF(
      MononokiFont_compressed_data_base85, 16.0f);

  static const ImWchar icon_glyph_ranges[] = {
      // 0x0000, 0x00FF, // ASCII
      0xe5fa, 0xe631, // Seti-UI + Custom
      0xe700, 0xe7c5, // Devicons
      0xf000, 0xf2e0, // Font Awesome
      0xe200, 0xe2a9, // Font Awesome Extension
      0xf500, 0xfd46, // Material Design Icons
      0xe300, 0xe3eb, // Weather
      0xf400, 0xf4a9, // Octicons (1)
      0x2665, 0x2665, // Octicons (2)
      0x26A1, 0x26A1, // Octicons (3)
      0xe0a0, 0xe0a2, // Powerline Symbols (1)
      0xe0b0, 0xe0b3, // Powerline Symbols (2)
      0xe0a3, 0xe0a3, // Powerline Extra Symbols (1)
      0xe0b4, 0xe0c8, // Powerline Extra Symbols (2)
      0xe0ca, 0xe0ca, // Powerline Extra Symbols (3)
      0xe0cc, 0xe0d4, // Powerline Extra Symbols (4)
      0x23fb, 0x23fe, // 2b58 // IEC Power Symbols
      0xf300, 0xf32d, // Font Logos
      0xe000, 0xe00a, // Pomicons
      0xea60, 0xebeb, // Codicons
      0};

  ImFontConfig config;
  config.MergeMode = true;
  config.GlyphOffset.x = -1.5f;
  config.GlyphOffset.y = -1.0f;
  io.Fonts->AddFontFromMemoryCompressedBase85TTF(
      MononokiFont_compressed_data_base85, 16.0f, &config, icon_glyph_ranges);

  io.Fonts->Build();
}

void initialize_application() {
  apply_style();
  // initialize_grid(app_state.editor_state.CANVAS_WIDTH,
  //                 app_state.editor_state.CANVAS_HEIGHT,
  //                 &app_state.editor_state);
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
  // ImGui::ShowDemoWindow();
  if ((app_state.editor_state.CANVAS_HEIGHT == 0) && (app_state.editor_state.CANVAS_WIDTH == 0)) render_dimensions_select();
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
