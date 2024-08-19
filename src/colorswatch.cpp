#include "imgui.h"
#include "utils.h"

void render_color_swatch() {
  const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(ImVec2(main_viewport->Size.x - 250,
                                 get_center(250.0f, main_viewport->Size.y)));
  ImGui::SetNextWindowSize(ImVec2(250, 250));

  ImGui::Begin("Color Swatch", NULL, WINDOW_FLAGS);
  ImGui::End();
}
