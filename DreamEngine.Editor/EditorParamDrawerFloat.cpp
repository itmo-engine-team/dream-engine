#include "EditorParamDrawerFloat.h"

#include "imgui.h"

EditorParamDrawerFloat::EditorParamDrawerFloat(int index, const std::string& name, BaseParam* baseParam)
    : EditorParamDrawer<ParamFloat>(index, name, baseParam)
{
    inputField = std::to_string(param->Get());
    inputField.resize(6);
    inputFieldLabel = "##" + std::to_string(index);
    resetButtonLabel = "X##" + std::to_string(index);
}

bool EditorParamDrawerFloat::Draw()
{
    ImGui::PushItemWidth(50);
    ImGui::Text(name.c_str());
    ImGui::SameLine();
    ImGui::InputText(inputFieldLabel.c_str(),
        inputField.data(), 6, ImGuiInputTextFlags_CharsDecimal);
    const bool isChanged = ImGui::IsItemDeactivatedAfterEdit();
    if (isChanged)
    {
        param->Set(std::stof(inputField.c_str()));
        return true;
    }

    ImGui::SameLine();
    if (ImGui::Button(resetButtonLabel.c_str()))
    {
        param->SetDef();
        inputField = std::to_string(param->Get());
        inputField.resize(6);

        return true;
    }

    ImGui::PopItemWidth();
    return false;
}
