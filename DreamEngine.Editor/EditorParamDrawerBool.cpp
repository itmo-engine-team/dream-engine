#include "EditorParamDrawerBool.h"

#include "imgui.h"

EditorParamDrawerBool::EditorParamDrawerBool(int index, const std::string& name, BaseParam* baseParam)
    : EditorParamDrawer<ParamBool>(index, name, baseParam)
{
    paramCheckBox = param->Get();

    checkboxLabel = "##" + std::to_string(index);
    resetButtonLabel = "X##" + std::to_string(index);
}

bool EditorParamDrawerBool::Draw()
{
    ImGui::Text(name.c_str());
    ImGui::SameLine();
    ImGui::Checkbox(checkboxLabel.c_str(), &paramCheckBox);
    const bool isChanged = ImGui::IsItemDeactivatedAfterEdit();
    if (isChanged)
    {
        param->Set(&paramCheckBox);
        return true;
    }

    ImGui::SameLine();
    if (ImGui::Button(resetButtonLabel.c_str()))
    {
        param->SetDef();
        paramCheckBox = param->Get();
        return true;
    }
    return false;
}
