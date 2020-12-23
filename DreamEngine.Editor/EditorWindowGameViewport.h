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

    const ImVec2 GAME_VIEWPORT_RATIO = ImVec2(16, 9);
    ImVec2 gameViewportSize;

    float gameViewportSizeMultiplier = 20;

    // for test 
    AssetTree* assetTree;
    FolderNode* currentScene = nullptr;

    void updateViewportSize();
    void renderGameViewport();
    void renderSceneHierarchy();

    void drawScenesTree(FolderNode* sceneNode);
    void drawSceneContextMenu();
    void drawActorContextMenu();
};

