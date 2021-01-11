#include "EditorParamDrawerTransform.h"

#include "imgui.h"

EditorParamDrawerTransform::EditorParamDrawerTransform(int index, const std::string& name, BaseParam* baseParam)
    : EditorParamDrawer<ParamTransform>(index, name, baseParam)
{
    inputFieldX = std::to_string(param->GetPosition().x);
    inputFieldX.resize(6);

    inputFieldY = std::to_string(param->GetPosition().y);
    inputFieldY.resize(6);

    inputFieldZ = std::to_string(param->GetPosition().z);
    inputFieldZ.resize(6);

    buttonLabel = "X##" + std::to_string(index);
    xPosLabel = "x##" + std::to_string(index);
    yPosLabel = "y##" + std::to_string(index);
    zPosLabel = "z##" + std::to_string(index);
}

bool EditorParamDrawerTransform::Draw()
{
    ImGui::Text("Position");
    ImGui::SameLine();
    if (ImGui::Button(buttonLabel.c_str()))
    {
        param->SetDefPosition();
        inputFieldX = std::to_string(param->GetPosition().x);
        inputFieldX.resize(6);

        inputFieldY = std::to_string(param->GetPosition().y);
        inputFieldY.resize(6);

        inputFieldZ = std::to_string(param->GetPosition().z);
        inputFieldZ.resize(6);

        return true;
    }

    ImGui::InputText(xPosLabel.c_str(),
        inputFieldX.data(), 6, ImGuiInputTextFlags_CharsDecimal);
    ImGui::InputText(yPosLabel.c_str(),
        inputFieldY.data(), 6, ImGuiInputTextFlags_CharsDecimal);
    ImGui::InputText(zPosLabel.c_str(),
        inputFieldZ.data(), 6, ImGuiInputTextFlags_CharsDecimal);

    const bool isChanged = ImGui::IsItemDeactivatedAfterEdit();
    if (isChanged)
    {
        param->SetPosition(Vector3(std::stof(inputFieldX.c_str()), std::stof(inputFieldY.c_str()), std::stof(inputFieldZ.c_str())));
        return true;
    }

    return false;
}
