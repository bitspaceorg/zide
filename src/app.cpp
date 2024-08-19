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

AppState app_state;

void initialize_application() {
  apply_style();
  initialize_grid(app_state.GRID_SIZE);
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
  render_grid();
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

static void initialize_grid(int size) {
  app_state.GRID_SIZE = size;
  app_state.pixelColors.resize(
      app_state.GRID_SIZE,
      std::vector<ImVec4>(app_state.GRID_SIZE, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)));
}

static void render_grid() {
  ImDrawList *drawList = ImGui::GetBackgroundDrawList();
  ImVec2 screenCenter = ImGui::GetIO().DisplaySize;
  screenCenter.x *= 0.5f;
  screenCenter.y *= 0.5f;
  ImVec2 gridTopLeft(
      screenCenter.x - (app_state.GRID_SIZE * app_state.PIXEL_SIZE / 2) +
          app_state.panOffset.x,
      screenCenter.y - (app_state.GRID_SIZE * app_state.PIXEL_SIZE / 2) +
          app_state.panOffset.y);

  ImVec2 gridBottomRight(
      screenCenter.x + (app_state.GRID_SIZE * app_state.PIXEL_SIZE / 2) +
          app_state.panOffset.x,
      screenCenter.y + (app_state.GRID_SIZE * app_state.PIXEL_SIZE / 2) +
          app_state.panOffset.y);
  ImVec2 windowSize = ImGui::GetIO().DisplaySize;

  double gridSize = app_state.GRID_SIZE * app_state.PIXEL_SIZE;
  double tileSize = gridSize / 8.0;

  for (double y = 0; y < gridSize; y += tileSize) {
    for (double x = 0; x < gridSize; x += tileSize) {
      ImVec2 pixelMin(gridTopLeft.x + x, gridTopLeft.y + y);
      ImVec2 pixelMax(pixelMin.x + tileSize, pixelMin.y + tileSize);

      ImU32 color =
          ((static_cast<int>(x / tileSize) + static_cast<int>(y / tileSize)) %
               2 ==
           0)
              ? ImColor(200, 200, 200, 255)
              : ImColor(150, 150, 150, 255);

      drawList->AddRectFilled(pixelMin, pixelMax, color);
    }
  }

  int startX =
      std::max(0, static_cast<int>(-gridTopLeft.x / app_state.PIXEL_SIZE));
  int startY =
      std::max(0, static_cast<int>(-gridTopLeft.y / app_state.PIXEL_SIZE));
  int endX = std::min(
      app_state.GRID_SIZE,
      static_cast<int>((windowSize.x - gridTopLeft.x) / app_state.PIXEL_SIZE) +
          1);
  int endY = std::min(
      app_state.GRID_SIZE,
      static_cast<int>((windowSize.y - gridTopLeft.y) / app_state.PIXEL_SIZE) +
          1);
  for (int y = startY; y < endY; y++) {
    for (int x = startX; x < endX; x++) {
      ImVec2 pixelMin(gridTopLeft.x + x * app_state.PIXEL_SIZE,
                      gridTopLeft.y + y * app_state.PIXEL_SIZE);
      ImVec2 pixelMax(pixelMin.x + app_state.PIXEL_SIZE,
                      pixelMin.y + app_state.PIXEL_SIZE);
      drawList->AddRectFilled(pixelMin, pixelMax,
                              ImColor(app_state.pixelColors[y][x]));
    }
  }

  static ImVec2 lastPixel(-1, -1);
  if (ImGui::IsMouseDown(0)) {
    ImVec2 mousePos = ImGui::GetMousePos();
    int x = (mousePos.x - gridTopLeft.x) / app_state.PIXEL_SIZE;
    int y = (mousePos.y - gridTopLeft.y) / app_state.PIXEL_SIZE;
    if (x >= 0 && x < app_state.GRID_SIZE && y >= 0 &&
        y < app_state.GRID_SIZE) {
if (lastPixel.x != -1 && lastPixel.y != -1) {
        int pixelDistanceX = abs(x - lastPixel.x);
        int pixelDistanceY = abs(y - lastPixel.y);
        int stepX = lastPixel.x < x ? 1 : -1;
        int stepY = lastPixel.y < y ? 1 : -1;
        int errorAccumulator = pixelDistanceX - pixelDistanceY;
        while (true) {
          if (lastPixel.x >= 0 && lastPixel.x < app_state.GRID_SIZE &&
              lastPixel.y >= 0 && lastPixel.y < app_state.GRID_SIZE) {
            app_state.pixelColors[lastPixel.y][lastPixel.x] =
                ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
            ImVec2 pixelMin(gridTopLeft.x + lastPixel.x * app_state.PIXEL_SIZE,
                            gridTopLeft.y + lastPixel.y * app_state.PIXEL_SIZE);
            ImVec2 pixelMax(pixelMin.x + app_state.PIXEL_SIZE,
                            pixelMin.y + app_state.PIXEL_SIZE);
            drawList->AddRectFilled(
                pixelMin, pixelMax,
                ImColor(app_state.pixelColors[lastPixel.y][lastPixel.x]));
          }
          if (lastPixel.x == x && lastPixel.y == y)
            break;

          int errorDouble = 2 * errorAccumulator;
          if (errorDouble > -pixelDistanceY) {
            errorAccumulator -= pixelDistanceY;
            lastPixel.x += stepX;
          }
          if (errorDouble < pixelDistanceX) {
            errorAccumulator += pixelDistanceX;
            lastPixel.y += stepY;
          }
        }
      }
      lastPixel = ImVec2(x, y);
    } else
      lastPixel = ImVec2(-1, -1);
  } else
    lastPixel = ImVec2(-1, -1);

  ImGuiIO &io = ImGui::GetIO();
  if (ImGui::IsMouseDragging(ImGuiMouseButton_Middle)) {
    if (!app_state.isPanning) {
      app_state.isPanning = true;
      app_state.lastMousePos = io.MousePos;
    }
    ImVec2 mouseDelta = ImVec2(io.MousePos.x - app_state.lastMousePos.x,
                               io.MousePos.y - app_state.lastMousePos.y);
    app_state.panOffset.x += mouseDelta.x;
    app_state.panOffset.y += mouseDelta.y;
    app_state.lastMousePos = io.MousePos;
  } else {
    app_state.isPanning = false;
  }
}

