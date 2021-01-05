#include "EditorWindowActorViewer.h"

#include "imgui.h"
#include "ModelAssetInfo.h"
#include "ModelViewer.h"
#include "ActorAssetInfo.h"

EditorWindowActorViewer::EditorWindowActorViewer(Editor* editor, ActorAssetInfo* actorAssetInfo)
    : EditorWindow("Actor Viewer", editor), actorAssetInfo(actorAssetInfo)
{
    if (actorAssetInfo == nullptr)
        SetOpened(false);
}

void EditorWindowActorViewer::Init()
{
    if (actorAssetInfo == nullptr)
        return;

    actorViewer = editor->GetContext()->GetActorViewer();

    reimportAsset();
}

void EditorWindowActorViewer::Update()
{
}

void EditorWindowActorViewer::Render()
{
    renderViewer();
    renderInspector();
}

void EditorWindowActorViewer::renderViewer()
{
    ImGui::Begin(GetName().c_str());
    
    if (ImGui::Button("Close"))
    {
        SetOpened(false);
    }

    ImGui::Separator();

    viewport->UpdateSize();
    ImGui::Image(actorViewer->GetSceneRenderer()->GetSceneResourceView(),
        viewport->GetSize());

    ImGui::End();
}

void EditorWindowActorViewer::renderInspector()
{
    ImGui::Begin("Actor Info");

    ImGui::Text(actorAssetInfo->GetName().c_str());

    ImGui::SameLine();
    if (ImGui::Button("Save"))
    {
        saveAsset();
    }

    ImGui::Separator();

    renderComponents();
    
    ImGui::Separator();

    // TODO render component info logic

    ImGui::End();
}

void EditorWindowActorViewer::renderComponents()
{
    auto flags = ImGuiTreeNodeFlags_OpenOnDoubleClick
        | ImGuiTreeNodeFlags_FramePadding
        | ImGuiTreeNodeFlags_Selected
        | ImGuiTreeNodeFlags_DefaultOpen
        | ImGuiTreeNodeFlags_NoTreePushOnOpen;

    // Scene Components
    bool treeExpanded = ImGui::TreeNodeEx("Scene Components", flags);
    renderSceneComponentsSectionPopup();
    if (treeExpanded)
    {
        for (auto component : actorAssetInfo->GetSceneComponents())
        {
            renderComponent(component);
        }
    }

    // Fixed Components
    treeExpanded = ImGui::TreeNodeEx("Fixed Components", flags);
    renderFixedComponentsSectionPopup();
    if (treeExpanded)
    {
        for (auto component : actorAssetInfo->GetFixedComponents())
        {
            renderComponent(component);
        }
    }
}

void EditorWindowActorViewer::renderComponent(ActorComponentInfo* component)
{
    auto flags = ImGuiTreeNodeFlags_FramePadding
        | ImGuiTreeNodeFlags_Leaf
        | ImGuiTreeNodeFlags_NoTreePushOnOpen;

    const std::string name = "  " + component->GetName();
    ImGui::TreeNodeEx(name.c_str(), flags);
}

void EditorWindowActorViewer::renderSceneComponentsSectionPopup()
{
    if (ImGui::BeginPopupContextItem())
    {
        for (auto iter : MAP_ACS_TYPE_TO_STRING)
        {
            if (ImGui::Selectable(iter.second.c_str()))
            {
                std::string name = iter.second
                    + "_" + std::to_string(actorAssetInfo->GetSceneComponents().size());
                actorAssetInfo->AddSceneComponent(iter.first, name);
            }
        }

        ImGui::EndPopup();
    }
}

void EditorWindowActorViewer::renderFixedComponentsSectionPopup()
{
    if (ImGui::BeginPopupContextItem())
    {
        for (auto iter : MAP_ACF_TYPE_TO_STRING)
        {
            if (ImGui::Selectable(iter.second.c_str()))
            {
                std::string name = iter.second
                    + "_" + std::to_string(actorAssetInfo->GetFixedComponents().size());
                actorAssetInfo->AddFixedComponent(iter.first, name);
            }
        }

        ImGui::EndPopup();
    }
}

void EditorWindowActorViewer::saveAsset()
{
    editor->GetContext()->GetAssetManager()->SaveAsset(actorAssetInfo->GetAssetNode());

    reimportAsset();
}

void EditorWindowActorViewer::reimportAsset()
{
    
}
