#pragma once

#include "EditorWindow.h"
#include "imgui.h"

#include "AssetTree.h"

class EditorWindowGameViewport : public EditorWindow
{

public:

    EditorWindowGameViewport(Editor* editor);

    void Update() override;
    void Render() override;


private:

    const ImVec2 GAME_VIEWPORT_RATION = ImVec2(16, 9);
    ImVec2 gameViewportSize;

    float gameViewportSizeMultiplier = 20;

    // for test 
    AssetTree* assetTree;
    FolderNode* currentScene = nullptr;

    void updateViewportSize();
    void renderGameEditorMenu();

    void drawScenesTree(FolderNode* sceneNode, int level = 0);
    void drawSceneContextMenu();
    void drawActorContextMenu();
};

