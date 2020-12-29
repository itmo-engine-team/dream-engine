#include "EditorWindowGameViewport.h"

#include "imgui.h"
#include "Editor.h"
#include "Graphics.h"
#include "Game.h"
#include "Scene.h"

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
}

void EditorWindowGameViewport::updateViewportSize()
{
    ImVec2 windowSize = ImGui::GetWindowSize();
    gameViewportSizeMultiplier = min(windowSize.x / GAME_VIEWPORT_RATIO.x, windowSize.y / GAME_VIEWPORT_RATIO.y);
    gameViewportSize = ImVec2(GAME_VIEWPORT_RATIO.x * gameViewportSizeMultiplier, GAME_VIEWPORT_RATIO.y * gameViewportSizeMultiplier);
}

void EditorWindowGameViewport::renderGameViewport()
{
    ImGui::Begin("GameViewport");

    if (ImGui::Button("Play")) 
    { 
        // TODO: Play game 
    }

    updateViewportSize();
    ImGui::Image(editor->GetContext()->GetGraphics()->GetSceneResourceView(), gameViewportSize);

    ImGui::End();
}

void EditorWindowGameViewport::renderSceneHierarchy()
{
    // Don't show additional windows if no scene is selected currently
    if (game->GetCurrentScene() == nullptr) return;

    if (currentScene != game->GetCurrentScene())
    {
        currentScene = game->GetCurrentScene();
    }

    ImGui::Begin("Scene Hierarchy");

    if (ImGui::Button("Save"))
    {
        // TODO: add SaveScene
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

    if (ImGui::TreeNodeEx(room->GetName().c_str(), flags))
    {
        treeExpanded = true;

        if (ImGui::IsItemClicked())
        {
            currentSceneRoom = room;
        }

        drawSceneContextMenu();

        for (auto actor : room->GetActors())
        {
            drawSceneHierarchyActor(actor);
        }
    }

    if (!treeExpanded)
    {
        if (ImGui::IsItemClicked())
        {
            currentSceneRoom = room;
        }

        drawSceneContextMenu();
    }
}

void EditorWindowGameViewport::drawSceneHierarchyActor(Actor* actor)
{
    auto flags = ImGuiTreeNodeFlags_Leaf
        | ImGuiTreeNodeFlags_FramePadding
        | ImGuiTreeNodeFlags_NoTreePushOnOpen;

    if (currentSceneActor == actor)
        flags |= ImGuiTreeNodeFlags_Selected;

    ImGui::TreeNodeEx(actor->GetActorInfo()->GetName().c_str(), flags);

    if (ImGui::IsItemClicked())
    {
        currentSceneActor = actor;
    }

    drawSceneContextMenu();
}

void EditorWindowGameViewport::drawSceneContextMenu()
{
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::Selectable("Edit"))
        {
            // TODO: add EditScene
        }

        if (ImGui::Selectable("Add prefab"))
        {
            // TODO: add AddPrefab
        }

        if (ImGui::Selectable("Add Actor"))
        {
            // TODO: add AddActor
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

void EditorWindowGameViewport::drawActorContextMenu()
{
    if (ImGui::BeginPopupContextItem())
    {
        if (ImGui::Selectable("Edit"))
        {
            // TODO: add EditActor
        }

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
