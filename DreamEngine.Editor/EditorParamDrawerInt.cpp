#include "EditorParamDrawerInt.h"

#include "imgui.h"

EditorParamDrawerInt::EditorParamDrawerInt(int index, const std::string& name, BaseParam* baseParam)
    : EditorParamDrawer<ParamInt>(index, name, baseParam)
{
    inputField = std::to_string(param->Get());
    inputField.resize(6);
    inputFieldLabel = name + "##" + std::to_string(index);
    buttonLabel = "X##" + std::to_string(index);
}

bool EditorParamDrawerInt::Draw()
{
    ImGui::InputText(inputFieldLabel.c_str(), 
        inputField.data(), 6, ImGuiInputTextFlags_CharsDecimal);
    const bool isChanged = ImGui::IsItemDeactivatedAfterEdit();
    if (isChanged)
    {
        param->Set(std::stoi(inputField.c_str()));
        return true;
    }

    ImGui::SameLine();
    if (ImGui::Button(buttonLabel.c_str()))
    {
        param->SetDef();
        inputField = std::to_string(param->Get());
        inputField.resize(6);

        return true;
    }
    return false;
}
