#include "app.h"
#include "editor.h"
#include "imgui.h"
#include "utils.h"
#include <cctype>
#include <iostream>

// Custom filter function to allow only digits
int InputTextFilterNaturalNumber(ImGuiInputTextCallbackData* data)
{
    if (data->EventChar < 256 && std::isdigit(data->EventChar))
        return 0;
    return 1;
}

void render_dimensions_select() {
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
    ImGui::SetNextWindowSize(ImVec2(300, 140));
    ImGui::Begin("Grid Dimensions", NULL, WINDOW_FLAGS);

    ImGui::Text("Select the dimensions for the grid:");
    ImGui::Separator();

    static char n_buf[64] = "";
    static char m_buf[64] = "";
    static int n = 0;
    static int m = 0;

    float window_width = ImGui::GetWindowWidth();
    float total_width = 60 * 2 + ImGui::CalcTextSize(" X ").x + ImGui::GetStyle().ItemSpacing.x * 2;
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

    float buttons_width = 120 * 2 + ImGui::GetStyle().ItemSpacing.x;
    offset = (window_width - buttons_width) * 0.5f;
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

    if (ImGui::BeginPopupModal("Invalid Input", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Please enter positive integers for both dimensions.");
        if (ImGui::Button("OK", ImVec2(120, 0))) { 
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }

    ImGui::End();
}
