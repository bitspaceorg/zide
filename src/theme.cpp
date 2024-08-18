#include "imgui.h"

void apply_style() {
  ImVec4 *colors = ImGui::GetStyle().Colors;
  colors[ImGuiCol_Text] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
  colors[ImGuiCol_TextDisabled] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);
  colors[ImGuiCol_WindowBg] = ImVec4(0.81f, 0.77f, 0.70f, 1.00f);
  colors[ImGuiCol_ChildBg] = ImVec4(0.81f, 0.77f, 0.70f, 1.00f);
  colors[ImGuiCol_PopupBg] = ImVec4(0.55f, 0.51f, 0.42f, 1.00f);
  colors[ImGuiCol_Border] = ImVec4(0.55f, 0.51f, 0.42f, 1.00f);
  colors[ImGuiCol_BorderShadow] = ImVec4(0.55f, 0.51f, 0.42f, 1.00f);
  colors[ImGuiCol_FrameBg] = ImVec4(0.91f, 0.91f, 0.91f, 1.00f);
  colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.90f, 0.90f, 0.40f);
  colors[ImGuiCol_FrameBgActive] = ImVec4(0.01f, 0.01f, 0.01f, 0.67f);
  colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
  colors[ImGuiCol_TitleBgActive] = ImVec4(0.01f, 0.01f, 0.01f, 1.00f);
  colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
  colors[ImGuiCol_MenuBarBg] = ImVec4(0.81f, 0.77f, 0.70f, 1.00f);
  colors[ImGuiCol_ScrollbarBg] = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
  colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
  colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
  colors[ImGuiCol_CheckMark] = ImVec4(0.67f, 0.61f, 0.92f, 1.00f);
  colors[ImGuiCol_SliderGrab] = ImVec4(0.67f, 0.61f, 0.92f, 1.00f);
  colors[ImGuiCol_SliderGrabActive] = ImVec4(0.58f, 0.49f, 0.92f, 1.00f);
  colors[ImGuiCol_Button] = ImVec4(0.67f, 0.61f, 0.92f, 1.00f);
  colors[ImGuiCol_ButtonHovered] = ImVec4(0.64f, 0.57f, 0.92f, 1.00f);
  colors[ImGuiCol_ButtonActive] = ImVec4(0.60f, 0.52f, 0.92f, 1.00f);
  colors[ImGuiCol_Header] = ImVec4(0.67f, 0.61f, 0.92f, 1.00f);
  colors[ImGuiCol_HeaderHovered] = ImVec4(0.65f, 0.56f, 0.94f, 1.00f);
  colors[ImGuiCol_HeaderActive] = ImVec4(0.61f, 0.51f, 0.95f, 1.00f);
  colors[ImGuiCol_Separator] = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
  colors[ImGuiCol_SeparatorHovered] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_SeparatorActive] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_ResizeGrip] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.48f, 0.48f, 0.57f, 1.00f);
  colors[ImGuiCol_ResizeGripActive] = ImVec4(0.52f, 0.52f, 0.62f, 1.00f);
  colors[ImGuiCol_TabHovered] = ImVec4(0.48f, 0.48f, 0.58f, 1.00f);
  colors[ImGuiCol_Tab] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_TabSelected] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_TabSelectedOverline] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_TabDimmed] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_TabDimmedSelected] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_TabDimmedSelectedOverline] =
      ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_DockingPreview] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_PlotLines] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_PlotHistogram] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_TableHeaderBg] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_TableBorderStrong] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_TableBorderLight] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_TableRowBg] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_TableRowBgAlt] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_TextLink] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_TextSelectedBg] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_DragDropTarget] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_NavHighlight] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
  colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.43f, 0.43f, 0.51f, 1.00f);
}

