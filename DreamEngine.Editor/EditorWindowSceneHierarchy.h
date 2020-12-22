#pragma once
#include "EditorWindow.h"

#include "AssetTree.h"

class EditorWindowSceneHierarchy : public EditorWindow
{
public:
    EditorWindowSceneHierarchy(Editor* editor);

    void Update() override;
    void Render() override;

private:

    // for test 
    AssetTree* assetTree;
    FolderNode* currentScene = nullptr;

    void drawScenesTree(FolderNode* sceneNode, int level = 0);
    void drawScenesTreeNodePadding(int level);
    void drawSceneContextMenu();
    void drawActorContextMenu();
};

