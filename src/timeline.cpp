#include "app.h"
#include "imgui.h"
#include "utils.h"
#include <editor.h>
#include <thread>
#include <undo_redo.h>

void animate() {
  while (app_state.timeline_state.is_animating) {
    app_state.timeline_state.active_frame =
        (app_state.timeline_state.active_frame + 1) % app_state.timeline_state.total_frames;
    std::this_thread::sleep_for( std::chrono::milliseconds(1000 / app_state.timeline_state.fps));
  };
};

void render_timeline() {
  const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(ImVec2(get_center(700.0f, main_viewport->Size.x), main_viewport->Size.y - 60));
  ImGui::SetNextWindowSize(ImVec2(700, 60));

  ImGui::Begin("Timeline", NULL, WINDOW_FLAGS);

  ImGui::Text("TIMELINE");
  ImGui::SameLine();

  ImVec2 available_space = ImGui::GetContentRegionAvail();

  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));  // Remove padding
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);       // Remove border size
  ImGui::BeginChild("Timeline - frames", ImVec2(available_space.x - 100.0f, 20.0f), true, ImGuiWindowFlags_NoDecoration);

  for (int i = 0; i < app_state.timeline_state.total_frames; i++) {
    std::string current_pos = std::to_string(i + 1);
    if (ImGui::Button(current_pos.c_str(), ImVec2(15, 20))) {
      app_state.timeline_state.active_frame = i;
    };
    ImGui::SameLine();
  };

  ImGui::EndChild();
  ImGui::PopStyleVar(2);
  ImGui::SameLine();

  if (ImGui::Button("+")) {
    add_frame(app_state.editor_state.CANVAS_WIDTH, app_state.editor_state.CANVAS_HEIGHT, &app_state.editor_state);
  }

  
  ImGui::SameLine();
  if (ImGui::Button("play")) {
    app_state.timeline_state.is_animating = !app_state.timeline_state.is_animating;

    if (app_state.timeline_state.is_animating) {
      app_state.timeline_state.active_frame = 0;
      std::thread(animate).detach();
    };

  };

  // if (ImGui::Button("undo")) {
  //   undo();
  // }
  //
  // ImGui::SameLine();
  // if (ImGui::Button("redo")) {
  //   redo();
  // }

  ImGui::End();
}
