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

    resetButtonLabel = "X##" + std::to_string(index);
    xPosLabel = "##" + std::to_string(index);
    yPosLabel = "##" + std::to_string(index+1);
    zPosLabel = "##" + std::to_string(index+2);
}

bool EditorParamDrawerTransform::Draw()
{
    ImGui::Text("Position");
    ImGui::SameLine();
    if (ImGui::Button(resetButtonLabel.c_str()))
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

    isChanged = false;

    ImGui::PushItemWidth(50);
    ImGui::Text("x");
    ImGui::SameLine();
    ImGui::InputText(xPosLabel.c_str(),
        inputFieldX.data(), 6, ImGuiInputTextFlags_CharsDecimal);
    if (ImGui::IsItemDeactivatedAfterChange())
    {
        param->SetPosition(Vector3(std::stof(inputFieldX.c_str()), std::stof(inputFieldY.c_str()), std::stof(inputFieldZ.c_str())));
        isChanged = true;
    }

    ImGui::SameLine();
    ImGui::Text(" y");
    ImGui::SameLine();
    ImGui::InputText(yPosLabel.c_str(),
        inputFieldY.data(), 6, ImGuiInputTextFlags_CharsDecimal);
    if (ImGui::IsItemDeactivatedAfterChange())
    {
        param->SetPosition(Vector3(std::stof(inputFieldX.c_str()), std::stof(inputFieldY.c_str()), std::stof(inputFieldZ.c_str())));
        isChanged = true;
    }

    ImGui::SameLine();
    ImGui::Text(" z");
    ImGui::SameLine();
    ImGui::InputText(zPosLabel.c_str(),
        inputFieldZ.data(), 6, ImGuiInputTextFlags_CharsDecimal);   
    if (ImGui::IsItemDeactivatedAfterChange())
    {
        param->SetPosition(Vector3(std::stof(inputFieldX.c_str()), std::stof(inputFieldY.c_str()), std::stof(inputFieldZ.c_str())));
        isChanged = true;
    }

    ImGui::PopItemWidth();
    return isChanged;
}
