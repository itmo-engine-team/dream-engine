#include "EditorParamDrawerInt.h"

#include "imgui.h"

EditorParamDrawerInt::EditorParamDrawerInt(int index, const std::string& name, BaseParam* baseParam)
    : EditorParamDrawer<ParamInt>(index, name, baseParam)
{
    inputField = std::to_string(param->Get());
    inputField.resize(6);
    inputFieldLabel = "##" + std::to_string(index);
    resetButtonLabel = "X##" + std::to_string(index);
}

bool EditorParamDrawerInt::Draw()
{
    bool isChanged = false;

    ImGui::PushItemWidth(50);
    ImGui::Text(name.c_str());
    ImGui::SameLine();
    ImGui::InputText(inputFieldLabel.c_str(), 
        inputField.data(), 6, ImGuiInputTextFlags_CharsDecimal);
    if (ImGui::IsItemDeactivatedAfterEdit())
    {
        param->Set(std::stoi(inputField.c_str()));
        isChanged = true;
    }

    ImGui::SameLine();
    if (ImGui::Button(resetButtonLabel.c_str()))
    {
        param->SetDef();
        inputField = std::to_string(param->Get());
        inputField.resize(6);

        isChanged = true;
    }

    ImGui::PopItemWidth();
    return isChanged;
}
