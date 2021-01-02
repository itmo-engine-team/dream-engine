#pragma once

#include "EditorWindow.h"
#include "EditorViewport.h"

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

    Game* game;
    Scene* currentScene;
    SceneRoom* currentSceneRoom;
    SceneActorInfo* currentSceneActor;

    EditorViewport* viewport = new EditorViewport();

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

