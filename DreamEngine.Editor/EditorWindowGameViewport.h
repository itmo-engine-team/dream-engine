#pragma once

#include "EditorWindow.h"
#include "EditorViewport.h"
#include "EditorParamDrawerTransform.h"
#include "EditorParamDrawerAsset.h"

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
    Scene* currentScene = nullptr;
    SceneRoom* currentSceneRoom = nullptr;
    SceneActorInfo* currentSceneActor = nullptr;

    EditorViewport* viewport = new EditorViewport();

    EditorParamDrawerTransform* paramDrawerCameraTransform = nullptr;
    EditorParamDrawerTransform* paramDrawerActorTransform = nullptr;
    EditorParamDrawerAsset* paramDrawerActorAsset = nullptr;

    std::string sceneActorName;

    void renderGameViewport();
    void renderSceneHierarchy();
    void renderRoomInspector();
    void renderActorInspector();

    void updateScene();
    void updateCurrentActor(SceneActorInfo* actorInfo);

    void drawSceneHierarchy();
    /*void drawSceneHierarchyRoom(SceneRoom* room);*/
    void drawSceneHierarchyActor(SceneActorInfo* actorInfo);
    void drawRoomContextMenu(SceneRoom* room);
    void drawActorContextMenu(SceneActorInfo* actorInfo);
};

