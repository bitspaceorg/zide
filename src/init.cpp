#include "app.h"
#include "editor.h"
#include "imgui.h"
#include "utils.h"
#include <cctype>
#include <cmath>

int InputTextFilterNaturalNumber(ImGuiInputTextCallbackData *data) {
  if (data->EventChar < 256 && std::isdigit(data->EventChar))
    return 0;
  return 1;
}

void render_dimensions_select() {
  int current_selected = 0;
  std::vector<std::pair<std::string, ColorSwatchState>> defaults{
      {"CALULATED",
       {.pallet =
            {
                Color{.name = "Color1",
                      .r = 56.0f / 255.0f,
                      .g = 59.0f / 255.0f,
                      .b = 107.0f / 255.0f,
                      .a = 1.0f}, // 3c3b6b
                Color{.name = "Color2",
                      .r = 108.0f / 255.0f,
                      .g = 120.0f / 255.0f,
                      .b = 174.0f / 255.0f,
                      .a = 1.0f}, // 6c78ae
                Color{.name = "Color3",
                      .r = 149.0f / 255.0f,
                      .g = 182.0f / 255.0f,
                      .b = 212.0f / 255.0f,
                      .a = 1.0f}, // 95b6d4
                Color{.name = "Color4",
                      .r = 80.0f / 255.0f,
                      .g = 80.0f / 255.0f,
                      .b = 101.0f / 255.0f,
                      .a = 1.0f}, // 505065
                Color{.name = "Color5",
                      .r = 192.0f / 255.0f,
                      .g = 193.0f / 255.0f,
                      .b = 216.0f / 255.0f,
                      .a = 1.0f}, // c0c1d8
                Color{.name = "Color6",
                      .r = 235.0f / 255.0f,
                      .g = 239.0f / 255.0f,
                      .b = 255.0f / 255.0f,
                      .a = 1.0f}, // ebefff
                Color{.name = "Color7",
                      .r = 172.0f / 255.0f,
                      .g = 156.0f / 255.0f,
                      .b = 135.0f / 255.0f,
                      .a = 1.0f}, // ac9c87
                Color{.name = "Color8",
                      .r = 238.0f / 255.0f,
                      .g = 236.0f / 255.0f,
                      .b = 207.0f / 255.0f,
                      .a = 1.0f}, // eeeccf
                Color{.name = "Color9",
                      .r = 110.0f / 255.0f,
                      .g = 134.0f / 255.0f,
                      .b = 96.0f / 255.0f,
                      .a = 1.0f}, // 6e8660
                Color{.name = "Color10",
                      .r = 60.0f / 255.0f,
                      .g = 61.0f / 255.0f,
                      .b = 50.0f / 255.0f,
                      .a = 1.0f} // 3c3d32
            },
        .current_active = 0}},
      {"WOODBLOCK",
       {.pallet =
            {
                Color{.name = "Color1",
                      .r = 43.0f / 255.0f,
                      .g = 40.0f / 255.0f,
                      .b = 33.0f / 255.0f,
                      .a = 1.0f}, // 2b2821
                Color{.name = "Color2",
                      .r = 98.0f / 255.0f,
                      .g = 76.0f / 255.0f,
                      .b = 60.0f / 255.0f,
                      .a = 1.0f}, // 624c3c
                Color{.name = "Color3",
                      .r = 217.0f / 255.0f,
                      .g = 172.0f / 255.0f,
                      .b = 139.0f / 255.0f,
                      .a = 1.0f}, // d9ac8b
                Color{.name = "Color4",
                      .r = 227.0f / 255.0f,
                      .g = 207.0f / 255.0f,
                      .b = 180.0f / 255.0f,
                      .a = 1.0f}, // e3cfb4
                Color{.name = "Color5",
                      .r = 36.0f / 255.0f,
                      .g = 61.0f / 255.0f,
                      .b = 92.0f / 255.0f,
                      .a = 1.0f}, // 243d5c
                Color{.name = "Color6",
                      .r = 93.0f / 255.0f,
                      .g = 114.0f / 255.0f,
                      .b = 117.0f / 255.0f,
                      .a = 1.0f}, // 5d7275
                Color{.name = "Color7",
                      .r = 92.0f / 255.0f,
                      .g = 139.0f / 255.0f,
                      .b = 147.0f / 255.0f,
                      .a = 1.0f}, // 5c8b93
                Color{.name = "Color8",
                      .r = 177.0f / 255.0f,
                      .g = 165.0f / 255.0f,
                      .b = 141.0f / 255.0f,
                      .a = 1.0f}, // b1a58d
                Color{.name = "Color9",
                      .r = 176.0f / 255.0f,
                      .g = 58.0f / 255.0f,
                      .b = 72.0f / 255.0f,
                      .a = 1.0f}, // b03a48
                Color{.name = "Color10",
                      .r = 212.0f / 255.0f,
                      .g = 128.0f / 255.0f,
                      .b = 77.0f / 255.0f,
                      .a = 1.0f}, // d4804d
                Color{.name = "Color11",
                      .r = 224.0f / 255.0f,
                      .g = 200.0f / 255.0f,
                      .b = 114.0f / 255.0f,
                      .a = 1.0f}, // e0c872
                Color{.name = "Color12",
                      .r = 62.0f / 255.0f,
                      .g = 105.0f / 255.0f,
                      .b = 88.0f / 255.0f,
                      .a = 1.0f} // 3e6958
            },

        .current_active = 0}},
      {"CRIMSON",
       {.pallet =
            {
                Color{.name = "Color1",
                      .r = 43.0f / 255.0f,
                      .g = 40.0f / 255.0f,
                      .b = 33.0f / 255.0f,
                      .a = 1.0f}, // 2b2821
                Color{.name = "Color2",
                      .r = 98.0f / 255.0f,
                      .g = 76.0f / 255.0f,
                      .b = 60.0f / 255.0f,
                      .a = 1.0f}, // 624c3c
                Color{.name = "Color3",
                      .r = 217.0f / 255.0f,
                      .g = 172.0f / 255.0f,
                      .b = 139.0f / 255.0f,
                      .a = 1.0f}, // d9ac8b
                Color{.name = "Color4",
                      .r = 227.0f / 255.0f,
                      .g = 207.0f / 255.0f,
                      .b = 180.0f / 255.0f,
                      .a = 1.0f}, // e3cfb4
                Color{.name = "Color5",
                      .r = 36.0f / 255.0f,
                      .g = 61.0f / 255.0f,
                      .b = 92.0f / 255.0f,
                      .a = 1.0f}, // 243d5c
                Color{.name = "Color6",
                      .r = 93.0f / 255.0f,
                      .g = 114.0f / 255.0f,
                      .b = 117.0f / 255.0f,
                      .a = 1.0f}, // 5d7275
                Color{.name = "Color7",
                      .r = 92.0f / 255.0f,
                      .g = 139.0f / 255.0f,
                      .b = 147.0f / 255.0f,
                      .a = 1.0f}, // 5c8b93
                Color{.name = "Color8",
                      .r = 177.0f / 255.0f,
                      .g = 165.0f / 255.0f,
                      .b = 141.0f / 255.0f,
                      .a = 1.0f}, // b1a58d
                Color{.name = "Color9",
                      .r = 176.0f / 255.0f,
                      .g = 58.0f / 255.0f,
                      .b = 72.0f / 255.0f,
                      .a = 1.0f}, // b03a48
                Color{.name = "Color10",
                      .r = 212.0f / 255.0f,
                      .g = 128.0f / 255.0f,
                      .b = 77.0f / 255.0f,
                      .a = 1.0f}, // d4804d
                Color{.name = "Color11",
                      .r = 224.0f / 255.0f,
                      .g = 200.0f / 255.0f,
                      .b = 114.0f / 255.0f,
                      .a = 1.0f}, // e0c872
                Color{.name = "Color12",
                      .r = 62.0f / 255.0f,
                      .g = 105.0f / 255.0f,
                      .b = 88.0f / 255.0f,
                      .a = 1.0f}, // 3e6958
                Color{.name = "Color13",
                      .r = 255.0f / 255.0f,
                      .g = 5.0f / 255.0f,
                      .b = 70.0f / 255.0f,
                      .a = 1.0f}, // ff0546
                Color{.name = "Color14",
                      .r = 156.0f / 255.0f,
                      .g = 23.0f / 255.0f,
                      .b = 59.0f / 255.0f,
                      .a = 1.0f}, // 9c173b
                Color{.name = "Color15",
                      .r = 102.0f / 255.0f,
                      .g = 15.0f / 255.0f,
                      .b = 49.0f / 255.0f,
                      .a = 1.0f}, // 660f31
                Color{.name = "Color16",
                      .r = 69.0f / 255.0f,
                      .g = 3.0f / 255.0f,
                      .b = 39.0f / 255.0f,
                      .a = 1.0f}, // 450327
                Color{.name = "Color17",
                      .r = 39.0f / 255.0f,
                      .g = 0.0f / 255.0f,
                      .b = 34.0f / 255.0f,
                      .a = 1.0f}, // 270022
                Color{.name = "Color18",
                      .r = 23.0f / 255.0f,
                      .g = 0.0f / 255.0f,
                      .b = 29.0f / 255.0f,
                      .a = 1.0f}, // 17001d
                Color{.name = "Color19",
                      .r = 9.0f / 255.0f,
                      .g = 1.0f / 255.0f,
                      .b = 13.0f / 255.0f,
                      .a = 1.0f}, // 09010d
                Color{.name = "Color20",
                      .r = 12.0f / 255.0f,
                      .g = 230.0f / 255.0f,
                      .b = 242.0f / 255.0f,
                      .a = 1.0f}, // 0ce6f2
                Color{.name = "Color21",
                      .r = 0.0f / 255.0f,
                      .g = 152.0f / 255.0f,
                      .b = 219.0f / 255.0f,
                      .a = 1.0f}, // 0098db
                Color{.name = "Color22",
                      .r = 30.0f / 255.0f,
                      .g = 87.0f / 255.0f,
                      .b = 156.0f / 255.0f,
                      .a = 1.0f}, // 1e579c
            },
        .current_active = 0}},
  };

  ImVec2 center = ImGui::GetMainViewport()->GetCenter();
  ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

  int num_palette_rows = (int)std::ceil(defaults.size() / 2.0f);
  float window_height = 200 + num_palette_rows * 30;
  ImGui::SetNextWindowSize(ImVec2(300, window_height));

  ImGui::Begin("Grid Dimensions", NULL, WINDOW_FLAGS);

  ImGui::Text("Select the dimensions for the grid");
  ImGui::Separator();

  static char n_buf[64] = "";
  static char m_buf[64] = "";
  static int n = 0;
  static int m = 0;

  float window_width = ImGui::GetWindowWidth();
  float total_width = 60 * 2 + ImGui::CalcTextSize(" X ").x +
                      ImGui::GetStyle().ItemSpacing.x * 2;
  float offset = (window_width - total_width) * 0.5f;
  ImGui::SetCursorPosX(offset);

  ImGui::PushItemWidth(60);
  if (ImGui::InputText("##n", n_buf, IM_ARRAYSIZE(n_buf),
                       ImGuiInputTextFlags_CallbackCharFilter,
                       InputTextFilterNaturalNumber)) {
    n = std::max(1, atoi(n_buf));
  }
  ImGui::SameLine();
  ImGui::Text(" X ");
  ImGui::SameLine();
  if (ImGui::InputText("##m", m_buf, IM_ARRAYSIZE(m_buf),
                       ImGuiInputTextFlags_CallbackCharFilter,
                       InputTextFilterNaturalNumber)) {
    m = std::max(1, atoi(m_buf));
  }
  ImGui::PopItemWidth();

  ImGui::Spacing();
  ImGui::Separator();
  ImGui::Text("Select a default color palette");

  float button_width = (window_width - ImGui::GetStyle().ItemSpacing.x * 3) / 2;
  float button_height = 25;
  for (size_t i = 0; i < defaults.size(); i += 2) {
    float row_width = (i + 1 < defaults.size())
                          ? (button_width * 2 + ImGui::GetStyle().ItemSpacing.x)
                          : button_width;
    offset = (window_width - row_width) * 0.5f;
    ImGui::SetCursorPosX(offset);

    for (size_t j = i; j < std::min(i + 2, defaults.size()); ++j) {
      const bool is_selected = (j == current_selected);

      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
      ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

      if (ImGui::Button(defaults[j].first.c_str(),
                        ImVec2(button_width, button_height))) {
        current_selected = j;
        app_state.color_swatch_state = defaults[j].second;
      }

      ImGui::PopStyleColor(2);

      if (j < i + 1 && j + 1 < defaults.size()) {
        ImGui::SameLine();
      }
    }
  }

  ImGui::Separator();

  float ok_cancel_width = 120 * 2 + ImGui::GetStyle().ItemSpacing.x;
  offset = (window_width - ok_cancel_width) * 0.5f;
  ImGui::SetCursorPosX(offset);

  if (ImGui::Button("OK", ImVec2(120, 0))) {
    n = atoi(n_buf);
    m = atoi(m_buf);
    if (n > 0 && m > 0) {
      initialize_grid(n, m, &app_state.editor_state);
      app_state.editor_state.changing_dimensions = false;
      ImGui::CloseCurrentPopup();
    } else {
      ImGui::OpenPopup("Invalid Input");
    }
  }
  ImGui::SameLine();
  if (ImGui::Button("Cancel", ImVec2(120, 0))) {
    app_state.editor_state.changing_dimensions = false;
    ImGui::CloseCurrentPopup();
  }

  if (ImGui::BeginPopupModal("Invalid Input", NULL,
                             ImGuiWindowFlags_AlwaysAutoResize)) {
    ImGui::Text("Please enter positive integers for both dimensions.");
    if (ImGui::Button("OK", ImVec2(120, 0))) {
      ImGui::CloseCurrentPopup();
    }
    ImGui::EndPopup();
  }

  ImGui::End();
}
