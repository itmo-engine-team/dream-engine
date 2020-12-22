#include "EditorWindowSceneHierarchy.h"

#include "Editor.h"
#include "AssetManager.h"

#include "imgui.h"

EditorWindowSceneHierarchy::EditorWindowSceneHierarchy(Editor* editor)
    : EditorWindow("Scene Hierarchy", editor)
{
    assetTree = editor->GetAssetManager()->GetContentAssetTree();
    currentScene = assetTree->GetRootNode();
}

void EditorWindowSceneHierarchy::Update()
{

}

void EditorWindowSceneHierarchy::Render()
{
    ImGui::Begin(GetName().data());

    if(ImGui::Button("Save"))
    {
        // TODO: add SaveScene
    }

    drawScenesTree(currentScene);

    ImGui::End();
}
 
void EditorWindowSceneHierarchy::drawScenesTree(FolderNode* sceneNode, int level)
{
    drawScenesTreeNodePadding(level);

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

void EditorWindowSceneHierarchy::drawScenesTreeNodePadding(int level)
{
    if (level == 0) return;

    const static std::string PADDING_CONST = " ";
    std::string padding;

    for (int i = 0; i < level; i++)
    {
        padding += PADDING_CONST;
    }
    ImGui::Text(padding.data());
    ImGui::SameLine();
}

void EditorWindowSceneHierarchy::drawSceneContextMenu()
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

void EditorWindowSceneHierarchy::drawActorContextMenu()
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
