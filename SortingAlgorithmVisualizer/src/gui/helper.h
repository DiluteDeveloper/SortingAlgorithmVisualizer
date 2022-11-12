#pragma once

#include <imgui/imgui.h>

bool DragU32(const char* label, unsigned int* value, unsigned int min, unsigned int max) {
    return ImGui::DragScalar(label, ImGuiDataType_U32, value, 1, &min, &max);
}
