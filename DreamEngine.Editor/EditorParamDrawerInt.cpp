#include "EditorParamDrawerInt.h"

#include "imgui.h"

EditorParamDrawerInt::EditorParamDrawerInt(const std::string& name, BaseParam* baseParam)
    : EditorParamDrawer<ParamInt>(name, baseParam)
{
    inputField.resize(6);
}

bool EditorParamDrawerInt::Draw()
{
    ImGui::InputText(name.c_str(), inputField.data(), 6, ImGuiInputTextFlags_CharsDecimal);
    const bool isChanged = ImGui::IsItemDeactivatedAfterEdit();
    if (!isChanged) return false;

    param->Set(std::stoi(inputField.c_str()));
    return true;
}
