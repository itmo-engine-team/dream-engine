#include "EditorWindowGameViewport.h"

#include "imgui.h"
#include "Editor.h"
#include "Graphics.h"
#include "Game.h"
#include "Scene.h"
#include "SceneActorInfo.h"
#include "SceneRoomInfo.h"
#include "SceneAssetInfo.h"

#include "AssetManager.h"

EditorWindowGameViewport::EditorWindowGameViewport(Editor* editor)
    : EditorWindow("Game Viewport", editor)
{
    game = editor->GetContext()->GetGame();
}

void EditorWindowGameViewport::Update()
{

}

void EditorWindowGameViewport::Render()
{
    renderGameViewport();
    renderSceneHierarchy();
    renderRoomInspector();
    renderActorInspector();
}

void EditorWindowGameViewport::renderGameViewport()
{
    ImGui::Begin("GameViewport");

    if (ImGui::Button("Play")) 
    { 
        // TODO: Play game 
    }

    viewport->UpdateSize();
    ImGui::Image(editor->GetContext()->GetGraphics()->GetSceneResourceView(), viewport->GetSize());

    ImGui::End();
}

void EditorWindowGameViewport::renderSceneHierarchy()
{
    // Don't show additional windows if no scene is selected currently
    if (game->GetCurrentScene() == nullptr) return;

    if (currentScene != game->GetCurrentScene())
    {
        currentScene = game->GetCurrentScene();
        currentSceneRoom = nullptr;
        currentSceneActor = nullptr;
    }

    ImGui::Begin("Scene Hierarchy");

    if (ImGui::Button("Save"))
    {
        auto sceneAssetNode = currentScene->GetSceneAssetInfo()->GetAssetNode();
        editor->GetContext()->GetAssetManager()->SaveAsset(sceneAssetNode);
    }

    ImGui::SameLine();
    if (ImGui::Button("Add Room"))
    {
        currentSceneRoom = currentScene->CreateNewRoom();
    }

    ImGui::Separator();

    drawSceneHierarchy();

    ImGui::End();
}

void EditorWindowGameViewport::renderRoomInspector()
{
    // Show room inspector only if room is selected and no actor is selected
    if (currentSceneRoom == nullptr || currentSceneActor != nullptr) return;

    ImGui::Begin("Room Inspector");

    ImGui::End();
}

void EditorWindowGameViewport::renderActorInspector()
{
    // Show only if actor is selected
    if (currentSceneActor == nullptr) return;

    ImGui::Begin("Actor Inspector");

    ImGui::End();
}

void EditorWindowGameViewport::drawSceneHierarchy()
{
    for (SceneRoom* room : currentScene->GetRoomList())
    {
        drawSceneHierarchyRoom(room);
    }
}

void EditorWindowGameViewport::drawSceneHierarchyRoom(SceneRoom* room)
{
    bool treeExpanded = false;

    auto flags = ImGuiTreeNodeFlags_OpenOnDoubleClick
        | ImGuiTreeNodeFlags_FramePadding
        | ImGuiTreeNodeFlags_NoTreePushOnOpen;

    if (currentSceneRoom == room)
        flags |= ImGuiTreeNodeFlags_Selected;

    if (ImGui::TreeNodeEx(room->GetRoomInfo()->GetName().c_str(), flags))
    {
        treeExpanded = true;

        if (ImGui::IsItemClicked())
        {
            currentSceneRoom = room;
            currentSceneActor = nullptr;
        }

        drawRoomContextMenu(room);

        for (auto actorInfo : room->GetRoomInfo()->GetActorInfoList())
        {
            drawSceneHierarchyActor(actorInfo);
        }
    }

    if (!treeExpanded)
    {
        if (ImGui::IsItemClicked())
        {
            currentSceneRoom = room;
            currentSceneActor = nullptr;
        }

        drawRoomContextMenu(room);
    }
}

void EditorWindowGameViewport::drawSceneHierarchyActor(SceneActorInfo* actorInfo)
{
    auto flags = ImGuiTreeNodeFlags_Leaf
        | ImGuiTreeNodeFlags_FramePadding
        | ImGuiTreeNodeFlags_NoTreePushOnOpen;

    if (currentSceneActor == actorInfo)
        flags |= ImGuiTreeNodeFlags_Selected;

    ImGui::TreeNodeEx(actorInfo->GetName().c_str(), flags);

    if (ImGui::IsItemClicked())
    {
        currentSceneActor = actorInfo;
    }

    drawActorContextMenu(actorInfo);
}

void EditorWindowGameViewport::drawRoomContextMenu(SceneRoom* room)
{
    if (ImGui::BeginPopupContextItem())
    {
        /*
        if (ImGui::Selectable("Add prefab"))
        {
            // TODO: add AddPrefab
        }*/

        if (ImGui::Selectable("Add Actor"))
        {
            room->CreateActor();
        }

        if (ImGui::Selectable("Delete"))
        {
            // TODO: add DeleteScene
        }

        if (ImGui::Selectable("Rename"))
        {
            // TODO: add RenameScene
        }

        ImGui::EndPopup();
    }
}

void EditorWindowGameViewport::drawActorContextMenu(SceneActorInfo* actorInfo)
{
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::Selectable("Save"))
        {
            // TODO: add SaveActor
        }

        if (ImGui::Selectable("Delete"))
        {
            // TODO: add DeleteActor
        }

        if (ImGui::Selectable("Rename"))
        {
            // TODO: add RenameActor
        }

        ImGui::EndPopup();
    }
}
