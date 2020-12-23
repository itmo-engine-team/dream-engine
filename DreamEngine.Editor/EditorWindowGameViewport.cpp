#include "EditorWindowGameViewport.h"

#include "imgui.h"
#include "Editor.h"
#include "Graphics.h"

#include "AssetManager.h"

EditorWindowGameViewport::EditorWindowGameViewport(Editor* editor)
    : EditorWindow("Game Viewport", editor)
{
    assetTree = editor->GetAssetManager()->GetContentAssetTree();
    currentScene = assetTree->GetRootNode();
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

void EditorWindowGameViewport::renderGameEditorMenu()
{
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New")) {}
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Editor"))
        {
            if (ImGui::MenuItem("Save Layout", "")) {}
            if (ImGui::MenuItem("Load Layout", "")) {}
            ImGui::Separator();
            if (ImGui::MenuItem("Close All ", "")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
}

void EditorWindowGameViewport::renderGameViewport()
{
    ImGui::Begin("GameViewport", nullptr, ImGuiWindowFlags_MenuBar);

    renderGameEditorMenu();

    if (ImGui::Button("Play")) 
    { 
        // TODO: Play game 
    }

    updateViewportSize();
    ImGui::Image(editor->GetGraphics()->GetSceneResourceView(), gameViewportSize);

    ImGui::End();
}

void EditorWindowGameViewport::renderSceneHierarchy()
{
    ImGui::Begin("Scene Hierarchy");

    if (ImGui::Button("Save"))
    {
        // TODO: add SaveScene
    }

    drawScenesTree(currentScene);

    ImGui::End();
}

void EditorWindowGameViewport::drawScenesTree(FolderNode* sceneNode)
{
    bool treeExpanded = false;

    auto flags = ImGuiTreeNodeFlags_OpenOnDoubleClick
        | ImGuiTreeNodeFlags_FramePadding
        | ImGuiTreeNodeFlags_NoTreePushOnOpen;

    if (currentScene == sceneNode)
        flags |= ImGuiTreeNodeFlags_Selected;

    if (ImGui::TreeNodeEx(sceneNode->GetName().c_str(), flags))
    {
        if (ImGui::IsItemClicked())
        {
            currentScene = sceneNode;
        }

        treeExpanded = true;

        currentScene = sceneNode;

        drawSceneContextMenu();

        for (auto childFolderNode : sceneNode->GetChildFolderList())
        {
            //drawFolderTreeNode(childFolderNode, level + 1);
        }
    }

    if (!treeExpanded)
    {
        if (ImGui::IsItemClicked())
        {
            currentScene = sceneNode;
        }

        drawSceneContextMenu();
    }
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
