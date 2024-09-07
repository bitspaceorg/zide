#include "imgui.h"
#include "app.h"
#include "utils.h"

const int pallet_columns = 4;

void render_color_swatch() {
  const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(ImVec2(main_viewport->Size.x - 150, get_center(200.0f, main_viewport->Size.y)));
  ImGui::SetNextWindowSize(ImVec2(150, 200));

  ImGui::Begin("Color Swatch", NULL, WINDOW_FLAGS);
	char buf[256] = ""; 

	auto [name, r, g, b, a] = app_state.color_swatch_state.pallet[app_state.color_swatch_state.current_active];

	Color& active_color = app_state.color_swatch_state.pallet[app_state.color_swatch_state.current_active];
  float color[4] = {active_color.r, active_color.g, active_color.b, active_color.a};
  
  ImGui::Text("CURRENT COLOR");

  if (ImGui::ColorEdit4("##picker", color, ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoInputs)) {
  	active_color.r = color[0];
    active_color.g = color[1];
    active_color.b = color[2];
    active_color.a = color[3];
  }

  ImGui::Spacing();
  ImGui::Separator();
  ImGui::Spacing();

  ImGui::Text("PALLET");
	ImVec2 child_size = ImVec2(0, ImGui::GetContentRegionAvail().y);
  ImGui::BeginChild("pallet", child_size, true);
  ImGui::Columns(pallet_columns, nullptr, false);

	for(int i=0; i < app_state.color_swatch_state.pallet.size(); i++) {
		auto [name, r, g, b, a] = app_state.color_swatch_state.pallet[i];
    ImVec4 pallet_indivdual_color(r,g, b, a);
    
		ImGui::PushID(i);
		if (ImGui::ColorButton("##Color", pallet_indivdual_color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_InputRGB, ImVec2(20,20))) {
      app_state.color_swatch_state.current_active = i;
		}
		ImGui::PopID();
    ImGui::NextColumn();
	}
  ImGui::Columns(1);
	ImGui::EndChild();
  ImGui::End();
};
