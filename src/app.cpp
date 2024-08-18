#include "app.h"
#include "imgui.h"
#include "utils.h"

AppState app_state;

void apply_style() {
  ImGuiStyle &style = ImGui::GetStyle();

  ImGui::StyleColorsDark();

  style.Alpha = 1.0f;
  style.WindowPadding = ImVec2(8, 8);
  style.WindowRounding = 7.0f;

  style.WindowBorderSize = 1.0f;

  style.WindowMinSize = ImVec2(32, 32);
  style.WindowTitleAlign = ImVec2(0.0f, 0.5f);
  style.ChildRounding = 0.0f;

  style.ChildBorderSize = 1.0f;

  style.PopupRounding = 0.0f;

  style.PopupBorderSize = 1.0f;

  style.FramePadding = ImVec2(4, 3);
  style.FrameRounding = 2.0f;

  style.FrameBorderSize = 1.0f;

  style.ItemSpacing = ImVec2(8, 4);
  style.ItemInnerSpacing = ImVec2(4, 4);

  style.TouchExtraPadding = ImVec2(0, 0);

  style.IndentSpacing = 21.0f;

  style.ColumnsMinSpacing = 6.0f;
  style.ScrollbarSize = 16.0f;

  style.ScrollbarRounding = 9.0f;
  style.GrabMinSize = 10.0f;
  style.GrabRounding = 2.0f;

  style.TabRounding = 4.0f;

  style.TabBorderSize = 1.0f;
  style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
  style.DisplayWindowPadding = ImVec2(20, 20);

  style.DisplaySafeAreaPadding = ImVec2(3, 3);

  style.MouseCursorScale = 1.0f;

  style.AntiAliasedLines = true;

  style.AntiAliasedFill = true;

  style.CurveTessellationTol = 1.25f;

  style.WindowMenuButtonPosition = ImGuiDir_None;

  ImVec4 *colors = ImGui::GetStyle().Colors;
  colors[ImGuiCol_Text] = ImVec4(0.96f, 0.96f, 0.96f, 0.88f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.96f, 0.96f, 0.96f, 0.28f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.09f, 0.96f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.09f, 0.09f, 0.09f, 0.96f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.18f, 0.18f, 0.18f, 0.96f);
  colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 0.31f, 0.60f);
  colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.96f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.25f, 0.95f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.09f, 0.42f, 0.26f, 0.96f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.25f, 0.25f, 0.25f, 0.95f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.09f, 0.42f, 0.26f, 0.96f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.09f, 0.42f, 0.26f, 0.96f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.09f, 0.09f, 0.09f, 0.96f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(0.15f, 0.15f, 0.15f, 0.96f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 0.93f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.25f, 0.25f, 0.25f, 0.95f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.09f, 0.42f, 0.26f, 0.96f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.96f, 0.96f, 0.96f, 0.88f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.31f, 0.31f, 0.31f, 0.93f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.15f, 0.15f, 0.15f, 0.96f);
  colors[ImGuiCol_Button] = ImVec4(0.15f, 0.15f, 0.15f, 0.96f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.25f, 0.25f, 0.95f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.09f, 0.42f, 0.26f, 0.96f);
  colors[ImGuiCol_Header] = ImVec4(0.25f, 0.25f, 0.25f, 0.95f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.31f, 0.31f, 0.31f, 0.93f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.09f, 0.42f, 0.26f, 0.96f);
  colors[ImGuiCol_Separator] = ImVec4(0.19f, 0.19f, 0.19f, 1.00f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.25f, 0.25f, 0.25f, 0.95f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(0.09f, 0.42f, 0.26f, 0.96f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.15f, 0.15f, 0.15f, 0.96f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.25f, 0.25f, 0.25f, 0.95f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(0.09f, 0.42f, 0.26f, 0.96f);
  colors[ImGuiCol_Tab] = ImVec4(0.05f, 0.21f, 0.13f, 0.96f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.26f, 0.71f, 0.49f, 0.96f);
  colors[ImGuiCol_TabActive] = ImVec4(0.17f, 0.52f, 0.35f, 0.96f);
  colors[ImGuiCol_TabUnfocused] = ImVec4(0.07f, 0.30f, 0.19f, 0.96f);
  colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.09f, 0.42f, 0.26f, 0.96f);
  colors[ImGuiCol_DockingPreview] = ImVec4(0.09f, 0.42f, 0.26f, 0.96f);
  colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_PlotLines] = ImVec4(0.96f, 0.96f, 0.96f, 0.80f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 0.25f, 0.25f, 0.95f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(0.96f, 0.96f, 0.96f, 0.80f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 0.25f, 0.25f, 0.95f);
  colors[ImGuiCol_TableHeaderBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_TableBorderStrong] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
  colors[ImGuiCol_TableBorderLight] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
  colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
  colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
  colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 0.25f, 0.25f, 0.95f);
  colors[ImGuiCol_DragDropTarget] = ImVec4(0.25f, 0.25f, 0.25f, 0.95f);
  colors[ImGuiCol_NavHighlight] = ImVec4(0.25f, 0.25f, 0.25f, 0.95f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.27f, 0.27f, 0.27f, 0.73f);
}

ImGuiWindowFlags WINDOWS_FLAG =
    0 | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoScrollbar |
    ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
    ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoBringToFrontOnFocus;

void initialize_application() {
  // apply_style();
}

void run_application() {
  // ImGui::ShowDemoWindow();
  render_main_menu_bar();
  if (app_state.is_timeline_visible) {
    render_timeline();
  }
  if (app_state.is_toolbar_visible) {
    render_toolbar();
  }
  if (app_state.is_colorswatch_visible) {
    render_color_swatch();
  }
};

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
      if (ImGui::MenuItem("Timeline")) {
      }
      if (ImGui::MenuItem("Toolbar")) {
      }
      if (ImGui::MenuItem("ColorSwatch")) {
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

static void render_toolbar() {
  const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(ImVec2(0, get_center(250.0f, main_viewport->Size.y)));
  ImGui::SetNextWindowSize(ImVec2(50, 250));

  ImGui::Begin("Toolbar", NULL, WINDOWS_FLAG);
  ImGui::End();
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
