#include "imgui.h"
#include "app.h"
#include "utils.h"
#include <iostream>
#include <string>

void render_color_swatch() {
  const ImGuiViewport *main_viewport = ImGui::GetMainViewport();
  ImGui::SetNextWindowPos(ImVec2(main_viewport->Size.x - 280,
                                 get_center(400.0f, main_viewport->Size.y)));
  ImGui::SetNextWindowSize(ImVec2(280, 400));

  ImGui::Begin("Color Swatch", NULL, WINDOW_FLAGS);
	char buf[256] = ""; 

	auto [name, r, g, b, a] = app_state.color_swatch_state.pallet[app_state.color_swatch_state.current_active];

	ImGuiColorEditFlags flags = ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_PickerHueWheel;
	Color& active_color = app_state.color_swatch_state.pallet[app_state.color_swatch_state.current_active];
  float color[4] = {active_color.r, active_color.g, active_color.b, active_color.a};
  
  if (ImGui::ColorPicker4("##picker", color, flags)) {
  	active_color.r = color[0];
    active_color.g = color[1];
    active_color.b = color[2];
    active_color.a = color[3];
  }

  ImGui::Spacing();
  ImGui::Separator();
  ImGui::Spacing();

	ImVec2 child_size = ImVec2(0, ImGui::GetContentRegionAvail().y - 50);
  ImGui::BeginChild("##ScrollableArea", child_size, true, ImGuiWindowFlags_AlwaysVerticalScrollbar);

	for(int i=0; i<app_state.color_swatch_state.pallet.size(); i++) {
		auto [name, r, g, b, a] = app_state.color_swatch_state.pallet[i];
		float new_col[4] = {r, g, b ,a};
		ImGui::PushID(i);
		bool checked = (i == app_state.color_swatch_state.current_active);
    if(ImGui::Checkbox("", &checked)){
			app_state.color_swatch_state.current_active = i;
		}
		ImGui::SameLine();
		if(ImGui::ColorEdit4("##Color", new_col)) {
			app_state.color_swatch_state.pallet[i].r = new_col[0];
			app_state.color_swatch_state.pallet[i].g = new_col[1];
			app_state.color_swatch_state.pallet[i].b = new_col[2];
			app_state.color_swatch_state.pallet[i].a = new_col[3];
		}
		ImGui::SameLine();
		ImGui::Text(name.c_str());
		ImGui::PopID();
	}
	ImGui::EndChild();

	ImGui::Spacing();
	ImGui::Separator();
	ImGui::Spacing();

  ImGui::End();
}

