#include "EditorParamDrawerTransform.h"

#include "imgui.h"

EditorParamDrawerTransform::EditorParamDrawerTransform(int index, const std::string& name, BaseParam* baseParam)
    : EditorParamDrawer<ParamTransform>(index, name, baseParam)
{
    inputFieldX = std::to_string(param->GetPosition().x);
    inputFieldX.resize(BUFFER_SIZE);

    inputFieldY = std::to_string(param->GetPosition().y);
    inputFieldY.resize(BUFFER_SIZE);

    inputFieldZ = std::to_string(param->GetPosition().z);
    inputFieldZ.resize(BUFFER_SIZE);

    resetButtonLabel = "X##" + std::to_string(index);
    xPosLabel = "##" + std::to_string(index);
    yPosLabel = "##" + std::to_string(index + 1);
    zPosLabel = "##" + std::to_string(index + 2);

    inputFieldRotationX = std::to_string(param->GetRotation().x);
    inputFieldRotationX.resize(BUFFER_SIZE);

    inputFieldRotationY = std::to_string(param->GetRotation().y);
    inputFieldRotationY.resize(BUFFER_SIZE);

    inputFieldRotationZ = std::to_string(param->GetRotation().z);
    inputFieldRotationZ.resize(BUFFER_SIZE);

    resetRotationButtonLabel = "X##" + std::to_string(index + 1);
    xRotationLabel = "##" + std::to_string(index + 3);
    yRotationLabel = "##" + std::to_string(index + 4);
    zRotationLabel = "##" + std::to_string(index + 5);
}

bool EditorParamDrawerTransform::Draw()
{
    bool isChanged = DrawPosition();
    isChanged = isChanged || DrawRotation();
    return isChanged;
}

bool EditorParamDrawerTransform::DrawPosition()
{
    ImGui::Text("Position");
    ImGui::SameLine();
    if (ImGui::Button(resetButtonLabel.c_str()))
    {
        param->SetDefPosition();
        inputFieldX = std::to_string(param->GetPosition().x);
        inputFieldX.resize(BUFFER_SIZE);

        inputFieldY = std::to_string(param->GetPosition().y);
        inputFieldY.resize(BUFFER_SIZE);

        inputFieldZ = std::to_string(param->GetPosition().z);
        inputFieldZ.resize(BUFFER_SIZE);

        return true;
    }

    bool isChanged = false;

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

bool EditorParamDrawerTransform::DrawRotation()
{
    ImGui::Text("Rotation");
    ImGui::SameLine();
    if (ImGui::Button(resetRotationButtonLabel.c_str()))
    {
        param->SetDefRotation();
        inputFieldRotationX = std::to_string(param->GetRotation().x);
        inputFieldRotationX.resize(BUFFER_SIZE);

        inputFieldRotationY = std::to_string(param->GetRotation().y);
        inputFieldRotationY.resize(BUFFER_SIZE);

        inputFieldRotationZ = std::to_string(param->GetRotation().z);
        inputFieldRotationZ.resize(BUFFER_SIZE);

        return true;
    }

    bool isChanged = false;

    ImGui::PushItemWidth(50);
    ImGui::Text("x");
    ImGui::SameLine();
    ImGui::InputText(xRotationLabel.c_str(),
        inputFieldRotationX.data(), 6, ImGuiInputTextFlags_CharsDecimal);
    if (ImGui::IsItemDeactivatedAfterChange())
    {
        param->SetRotation(Vector3(
            std::stof(inputFieldRotationX.c_str()),
            std::stof(inputFieldRotationY.c_str()),
            std::stof(inputFieldRotationZ.c_str())
        ));
        isChanged = true;
    }

    ImGui::SameLine();
    ImGui::Text(" y");
    ImGui::SameLine();
    ImGui::InputText(yRotationLabel.c_str(),
        inputFieldRotationY.data(), 6, ImGuiInputTextFlags_CharsDecimal);
    if (ImGui::IsItemDeactivatedAfterChange())
    {
        param->SetRotation(Vector3(
            std::stof(inputFieldRotationX.c_str()),
            std::stof(inputFieldRotationY.c_str()),
            std::stof(inputFieldRotationZ.c_str())
        ));
        isChanged = true;
    }

    ImGui::SameLine();
    ImGui::Text(" z");
    ImGui::SameLine();
    ImGui::InputText(zRotationLabel.c_str(),
        inputFieldRotationZ.data(), 6, ImGuiInputTextFlags_CharsDecimal);
    if (ImGui::IsItemDeactivatedAfterChange())
    {
        param->SetRotation(Vector3(
            std::stof(inputFieldRotationX.c_str()),
            std::stof(inputFieldRotationY.c_str()),
            std::stof(inputFieldRotationZ.c_str())
        ));
        isChanged = true;
    }

    ImGui::PopItemWidth();
    return isChanged;
}
