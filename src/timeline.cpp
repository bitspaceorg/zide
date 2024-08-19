#include "imgui.h"
#include "utils.h"

void render_timeline() {
  const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(ImVec2(get_center(700.0f, main_viewport->Size.x),
                                 main_viewport->Size.y - 100));
  ImGui::SetNextWindowSize(ImVec2(700, 100));

  ImGui::Begin("Timeline", NULL, WINDOW_FLAGS);
  ImGui::End();
}
