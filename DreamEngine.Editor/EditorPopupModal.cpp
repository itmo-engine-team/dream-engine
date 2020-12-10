#include "EditorPopupModal.h"

#include "imgui.h"

EditorPopupModal::EditorPopupModal(std::string name) : name(std::move(name))
{
    ImGui::OpenPopup(this->name.data());
}

bool EditorPopupModal::IsFinished() const
{
    return isFinished;
}

bool EditorPopupModal::GetResult() const
{
    return result;
}

void EditorPopupModal::Draw()
{
    ImGui::SetNextWindowPos(ImGui::GetMainViewport()->GetCenter(),
        ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal(name.data(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        onDrawPopup();

        ImGui::Separator();

        if (ImGui::Button("OK", ImVec2(120, 0))) { finish(true); }
        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(120, 0))) { finish(false); }
        ImGui::EndPopup();
    }
}

void EditorPopupModal::finish(const bool isSuccess)
{
    result = isSuccess;
    isFinished = true;
    onFinish();

    ImGui::CloseCurrentPopup();
}
