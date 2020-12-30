#pragma once

#include "EditorWindow.h"
#include "imgui.h"

class SceneActorInfo;
class Game;
class Scene;
class SceneRoom;
class Actor;

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

    Game* game;
    Scene* currentScene;
    SceneRoom* currentSceneRoom;
    SceneActorInfo* currentSceneActor;

    void updateViewportSize();
    void renderGameViewport();
    void renderSceneHierarchy();
    void renderRoomInspector();
    void renderActorInspector();

    void drawSceneHierarchy();
    void drawSceneHierarchyRoom(SceneRoom* room);
    void drawSceneHierarchyActor(SceneActorInfo* actorInfo);
    void drawRoomContextMenu(SceneRoom* room);
    void drawActorContextMenu(SceneActorInfo* actorInfo);
};

