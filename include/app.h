#include <string>
#include <vector>

enum SelectedTool { SELECTED_PENCIL, SELECTED_ERASER, SELECTED_BUCKET };
struct ToolBar {
  SelectedTool selected_tool = SELECTED_PENCIL;
  int pencil_size = 10;
  int eraser_size = 10;
};

struct Timeline {
  int fps = 24;
  int total_frames = 1;
  int current_seekhead = 0;
};

struct Color {
  std::string name;
  float r, g, b, a;
};
struct ColorSwatch {
  std::vector<Color> pallet{
      Color{.name = "black", .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f},
      Color{.name = "white", .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f},
      Color{.name = "red", .r = 0.0f, .g = 0.0f, .b = 0.0f, .a = 1.0f}};
  int current_active = 0;
};

struct AppState {
  bool is_timeline_visible = true;
  bool is_toolbar_visible = true;
  bool is_colorswatch_visible = true;

  ToolBar toolbar_state;
  Timeline timeline;
  ColorSwatch color_swatch;
};
extern AppState app_state;

void run_application();
void initialize_application();
static void render_toolbar();
static void render_main_menu_bar();
static void render_timeline();
static void render_color_swatch();
