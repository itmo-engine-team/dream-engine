#include "EditorParamDrawerString.h"

#include "imgui.h"

EditorParamDrawerString::EditorParamDrawerString(int index, const std::string& name, BaseParam* baseParam)
    : EditorParamDrawer<ParamString>(index, name, baseParam)
{
    inputField = param->Get();
    inputField.resize(15);
    inputFieldLabel = "##" + std::to_string(index);
    resetButtonLabel = "X##" + std::to_string(index);
}

bool EditorParamDrawerString::Draw()
{
    bool isChanged = false;

    ImGui::PushItemWidth(50);
    ImGui::Text(name.c_str());
    ImGui::SameLine();
    ImGui::InputText(inputFieldLabel.c_str(),
        inputField.data(), 15, ImGuiInputTextFlags_CharsNoBlank);
    if (ImGui::IsItemDeactivatedAfterEdit())
    {
        param->Set(inputField.c_str());
        isChanged = true;
    }

    ImGui::SameLine();
    if (ImGui::Button(resetButtonLabel.c_str()))
    {
        param->SetDef();
        inputField = param->Get();
        inputField.resize(15);

        isChanged = true;
    }

    ImGui::PopItemWidth();
    return isChanged;
}

