#include "EditorParamDrawerTransform.h"

#include "imgui.h"

EditorParamDrawerTransform::EditorParamDrawerTransform(int index, const std::string& name, BaseParam* baseParam)
    : EditorParamDrawer<ParamTransform>(index, name, baseParam)
{
    // Position
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

    // Rotation
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

    // Rotation
    inputFieldScaleX = std::to_string(param->GetScale().x);
    inputFieldScaleX.resize(BUFFER_SIZE);

    inputFieldScaleY = std::to_string(param->GetScale().y);
    inputFieldScaleY.resize(BUFFER_SIZE);

    inputFieldScaleZ = std::to_string(param->GetScale().z);
    inputFieldScaleZ.resize(BUFFER_SIZE);

    resetScaleButtonLabel = "X##" + std::to_string(index + 2);
    xScaleLabel = "##" + std::to_string(index + 6);
    yScaleLabel = "##" + std::to_string(index + 7);
    zScaleLabel = "##" + std::to_string(index + 8);
}

bool EditorParamDrawerTransform::Draw()
{
    bool isChanged = DrawPosition();
    isChanged = isChanged || DrawRotation();
    isChanged = isChanged || DrawScale();
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
        inputFieldX.data(), BUFFER_SIZE, ImGuiInputTextFlags_CharsDecimal);
    if (ImGui::IsItemDeactivatedAfterChange())
    {
        param->SetPosition(Vector3(std::stof(inputFieldX.c_str()), std::stof(inputFieldY.c_str()), std::stof(inputFieldZ.c_str())));
        isChanged = true;
    }

    ImGui::SameLine();
    ImGui::Text(" y");
    ImGui::SameLine();
    ImGui::InputText(yPosLabel.c_str(),
        inputFieldY.data(), BUFFER_SIZE, ImGuiInputTextFlags_CharsDecimal);
    if (ImGui::IsItemDeactivatedAfterChange())
    {
        param->SetPosition(Vector3(std::stof(inputFieldX.c_str()), std::stof(inputFieldY.c_str()), std::stof(inputFieldZ.c_str())));
        isChanged = true;
    }

    ImGui::SameLine();
    ImGui::Text(" z");
    ImGui::SameLine();
    ImGui::InputText(zPosLabel.c_str(),
        inputFieldZ.data(), BUFFER_SIZE, ImGuiInputTextFlags_CharsDecimal);
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
        inputFieldRotationX.data(), BUFFER_SIZE, ImGuiInputTextFlags_CharsDecimal);
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
        inputFieldRotationY.data(), BUFFER_SIZE, ImGuiInputTextFlags_CharsDecimal);
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
        inputFieldRotationZ.data(), BUFFER_SIZE, ImGuiInputTextFlags_CharsDecimal);
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

bool EditorParamDrawerTransform::DrawScale()
{
    ImGui::Text("Scale");
    ImGui::SameLine();
    if (ImGui::Button(resetScaleButtonLabel.c_str()))
    {
        param->SetDefScale();
        inputFieldScaleX = std::to_string(param->GetScale().x);
        inputFieldScaleX.resize(BUFFER_SIZE);

        inputFieldScaleY = std::to_string(param->GetScale().y);
        inputFieldScaleY.resize(BUFFER_SIZE);

        inputFieldScaleZ = std::to_string(param->GetScale().z);
        inputFieldScaleZ.resize(BUFFER_SIZE);

        return true;
    }

    bool isChanged = false;

    ImGui::PushItemWidth(50);
    ImGui::Text("x");
    ImGui::SameLine();
    ImGui::InputText(xScaleLabel.c_str(),
        inputFieldScaleX.data(), BUFFER_SIZE, ImGuiInputTextFlags_CharsDecimal);
    if (ImGui::IsItemDeactivatedAfterChange())
    {
        param->SetScale(Vector3(
            std::stof(inputFieldScaleX.c_str()),
            std::stof(inputFieldScaleY.c_str()),
            std::stof(inputFieldScaleZ.c_str())
        ));
        isChanged = true;
    }

    ImGui::SameLine();
    ImGui::Text(" y");
    ImGui::SameLine();
    ImGui::InputText(yScaleLabel.c_str(),
        inputFieldScaleY.data(), BUFFER_SIZE, ImGuiInputTextFlags_CharsDecimal);
    if (ImGui::IsItemDeactivatedAfterChange())
    {
        param->SetScale(Vector3(
            std::stof(inputFieldScaleX.c_str()),
            std::stof(inputFieldScaleY.c_str()),
            std::stof(inputFieldScaleZ.c_str())
        ));
        isChanged = true;
    }

    ImGui::SameLine();
    ImGui::Text(" z");
    ImGui::SameLine();
    ImGui::InputText(zScaleLabel.c_str(),
        inputFieldScaleZ.data(), BUFFER_SIZE, ImGuiInputTextFlags_CharsDecimal);
    if (ImGui::IsItemDeactivatedAfterChange())
    {
        param->SetScale(Vector3(
            std::stof(inputFieldScaleX.c_str()),
            std::stof(inputFieldScaleY.c_str()),
            std::stof(inputFieldScaleZ.c_str())
        ));
        isChanged = true;
    }

    ImGui::PopItemWidth();
    ImGui::Separator();
    return isChanged;
}
