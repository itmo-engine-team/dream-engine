#include "EditorParamDrawerString.h"

#include "imgui.h"

EditorParamDrawerString::EditorParamDrawerString(int index, const std::string& name, BaseParam* baseParam)
    : EditorParamDrawer<ParamString>(index, name, baseParam)
{
    inputField = param->Get();
    inputField.resize(6);
    inputFieldLabel ="##" + std::to_string(index);
    resetButtonLabel = "X##" + std::to_string(index);
}

bool EditorParamDrawerString::Draw()
{
    ImGui::PushItemWidth(50);
    ImGui::Text(name.c_str());
    ImGui::SameLine();
    ImGui::InputText(inputFieldLabel.c_str(),
        inputField.data(), 6, ImGuiInputTextFlags_CharsHexadecimal);
    const bool isChanged = ImGui::IsItemDeactivatedAfterEdit();
    if (isChanged)
    {
        param->Set(inputField.c_str());
        return true;
    }

    ImGui::SameLine();
    if (ImGui::Button(resetButtonLabel.c_str()))
    {
        param->SetDef();
        inputField = param->Get();
        inputField.resize(6);

        return true;
    }

    ImGui::PopItemWidth();
    return false;
}

