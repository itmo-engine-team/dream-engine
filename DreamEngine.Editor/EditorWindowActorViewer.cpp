#include "EditorWindowActorViewer.h"

#include "imgui.h"

#include "ActorAssetInfo.h"
#include "Editor.h"
#include "AssetManager.h"
#include "ActorComponent.h"
#include <MapUtils.h>

EditorWindowActorViewer::EditorWindowActorViewer(Editor* editor, ActorAssetInfo* actorAssetInfo)
    : EditorWindow("Actor Viewer", editor), actorAssetInfo(actorAssetInfo)
{
    if (actorAssetInfo == nullptr)
        SetOpened(false);

    sizeStr = MAP_ACTOR_TYPE_TO_STRING.size();
    tempStrMass = new std::string[sizeStr];
    int i = 0;

    for (auto iterator = MAP_ACTOR_TYPE_TO_STRING.begin(); iterator != MAP_ACTOR_TYPE_TO_STRING.end(); ++iterator, i++)
    {
        tempStrMass[i] = iterator->second;
    }
    selectableActorType = tempStrMass[0];
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
    renderSceneComponentInspector();
    renderFixedComponentInspector();
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

    renderActorTypeSelectable();
    renderComponents();
    
    ImGui::Separator();

    // TODO render component info logic

    ImGui::End();
}

void EditorWindowActorViewer::renderActorTypeSelectable()
{
    if(ImGui::BeginCombo("Actor Type", selectableActorType.data()))
    {
        for (int n = 0; n < sizeStr; n++)
        {
            const bool isSelected = (currentType == n);

            if (ImGui::Selectable(tempStrMass[n].c_str(), isSelected))
            {
                currentType = n;
                selectableActorType = tempStrMass[currentType];
                actorType = MapUtils::TryGetByValue<ActorType, std::string>(MAP_ACTOR_TYPE_TO_STRING, selectableActorType, ActorType::Unknown);
                actorAssetInfo->SetActorType(actorType);
            }
            if (isSelected)
                ImGui::SetItemDefaultFocus();
        }
        ImGui::EndCombo();
    }
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
            renderComponent(component, selectedSceneComponent == component);

            if (ImGui::IsItemClicked())
            {
                selectedSceneComponent = component;
                selectedFixedComponent = nullptr;

                delete paramViewer;
                paramViewer = new EditorParamViewer(editor, selectedSceneComponent->GetParamExtender());
            }
        }
    }

    // Fixed Components
    treeExpanded = ImGui::TreeNodeEx("Fixed Components", flags);
    renderFixedComponentsSectionPopup();
    if (treeExpanded)
    {
        for (auto component : actorAssetInfo->GetFixedComponents())
        {
            renderComponent(component, selectedFixedComponent == component);

            if (ImGui::IsItemClicked())
            {
                selectedFixedComponent = component;
                selectedSceneComponent = nullptr;

                delete paramViewer;
                paramViewer = new EditorParamViewer(editor, selectedFixedComponent->GetParamExtender());
            }
        }
    }
}

void EditorWindowActorViewer::renderComponent(ActorComponentInfo* component, bool isSelected)
{
    auto flags = ImGuiTreeNodeFlags_FramePadding
        | ImGuiTreeNodeFlags_Leaf
        | ImGuiTreeNodeFlags_NoTreePushOnOpen;

    if (isSelected)
        flags |= ImGuiTreeNodeFlags_Selected;

    const std::string name = "  " + component->GetName();
    ImGui::TreeNodeEx(name.c_str(), flags);
}

void EditorWindowActorViewer::renderSceneComponentInspector()
{
    if (selectedSceneComponent == nullptr)
        return;

    ImGui::Begin("Component Info");

    ImGui::Text(selectedSceneComponent->GetName().c_str());
    ImGui::Separator();

    renderComponentParams(selectedSceneComponent);

    ImGui::End();
}

void EditorWindowActorViewer::renderFixedComponentInspector()
{
    if (selectedFixedComponent == nullptr)
        return;

    ImGui::Begin("Component Info");

    ImGui::Text(selectedFixedComponent->GetName().c_str());
    ImGui::Separator();

    renderComponentParams(selectedFixedComponent);

    ImGui::End();
}

void EditorWindowActorViewer::renderComponentParams(ActorComponentInfo* componentInfo)
{
    BaseParam* baseParam = paramViewer->Draw();
    bool isChanged = baseParam != nullptr;

    if (isChanged)
    {
        for (auto iter : componentInfo->GetParamExtender()->GetParamMap())
        {
            if (baseParam == iter.second)
            {
                componentInfo->GetComponentRef()->UpdateParam(iter.first, baseParam);
            }
        }
    }
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
                actorViewer->AddSceneComponent(iter.first, name);
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
                actorViewer->AddFixedComponent(iter.first, name);
            }
        }

        ImGui::EndPopup();
    }
}

void EditorWindowActorViewer::saveAsset()
{
    editor->GetContext()->GetAssetManager()->SaveAsset(actorAssetInfo->GetAssetNode());
}

void EditorWindowActorViewer::reimportAsset()
{
    actorViewer->LoadActor(actorAssetInfo);
}
