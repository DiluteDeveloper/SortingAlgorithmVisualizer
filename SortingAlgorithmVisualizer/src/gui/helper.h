#pragma once

#include <imgui/imgui.h>

void DragU32(const char* label, unsigned int* value, unsigned int min, unsigned int max) {
    ImGui::DragScalar(label, ImGuiDataType_U32, value, 1, &min, &max);
}
