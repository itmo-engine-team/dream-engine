#include "EditorParamDrawerVector3.h"

#include "imgui.h"

EditorParamDrawerVector3::EditorParamDrawerVector3(int index, const std::string& name, BaseParam* baseParam)
    : EditorParamDrawer<ParamVector3>(index, name, baseParam)
{
    inputFieldX = std::to_string(param->Get().x);
    inputFieldX.resize(BUFFER_SIZE);

    inputFieldY = std::to_string(param->Get().y);
    inputFieldY.resize(BUFFER_SIZE);

    inputFieldZ = std::to_string(param->Get().z);
    inputFieldZ.resize(BUFFER_SIZE);

    resetButtonLabel = "X##" + std::to_string(index);
    xPosLabel = "##" + std::to_string(index);
    yPosLabel = "##" + std::to_string(index + 1);
    zPosLabel = "##" + std::to_string(index + 2);
}

bool EditorParamDrawerVector3::Draw()
{  
    ImGui::Text(name.c_str());
    ImGui::SameLine();
    if (ImGui::Button(resetButtonLabel.c_str()))
    {
        param->SetDef();
        inputFieldX = std::to_string(param->Get().x);
        inputFieldX.resize(BUFFER_SIZE);

        inputFieldY = std::to_string(param->Get().y);
        inputFieldY.resize(BUFFER_SIZE);

        inputFieldZ = std::to_string(param->Get().z);
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
        param->Set(Vector3(std::stof(inputFieldX.c_str()), std::stof(inputFieldY.c_str()), std::stof(inputFieldZ.c_str())));
        isChanged = true;
    }

    ImGui::SameLine();
    ImGui::Text(" y");
    ImGui::SameLine();
    ImGui::InputText(yPosLabel.c_str(),
        inputFieldY.data(), BUFFER_SIZE, ImGuiInputTextFlags_CharsDecimal);
    if (ImGui::IsItemDeactivatedAfterChange())
    {
        param->Set(Vector3(std::stof(inputFieldX.c_str()), std::stof(inputFieldY.c_str()), std::stof(inputFieldZ.c_str())));
        isChanged = true;
    }

    ImGui::SameLine();
    ImGui::Text(" z");
    ImGui::SameLine();
    ImGui::InputText(zPosLabel.c_str(),
        inputFieldZ.data(), BUFFER_SIZE, ImGuiInputTextFlags_CharsDecimal);
    if (ImGui::IsItemDeactivatedAfterChange())
    {
        param->Set(Vector3(std::stof(inputFieldX.c_str()), std::stof(inputFieldY.c_str()), std::stof(inputFieldZ.c_str())));
        isChanged = true;
    }

    ImGui::PopItemWidth();
    return isChanged;
}