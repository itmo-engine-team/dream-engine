#include "EditorParamDrawerInt.h"

#include "imgui.h"

EditorParamDrawerInt::EditorParamDrawerInt(int index, const std::string& name, BaseParam* baseParam)
    : EditorParamDrawer<ParamInt>(index, name, baseParam)
{
    inputField.resize(6);
    inputFieldLabel = name + "##" + std::to_string(index);
}

bool EditorParamDrawerInt::Draw()
{
    ImGui::InputText(inputFieldLabel.c_str(), 
        inputField.data(), 6, ImGuiInputTextFlags_CharsDecimal);
    const bool isChanged = ImGui::IsItemDeactivatedAfterEdit();
    if (!isChanged) return false;

    param->Set(std::stoi(inputField.c_str()));
    return true;
}
