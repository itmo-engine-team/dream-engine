#include "EditorWindowGameViewport.h"

#include "imgui.h"
#include "Editor.h"
#include "Game.h"
#include "Scene.h"
#include "SceneActorInfo.h"
#include "SceneRoomInfo.h"
#include "SceneAssetInfo.h"

#include "AssetManager.h"
#include "Actor.h"

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

    // Don't show additional windows if no scene is selected currently
    if (game->GetCurrentScene() == nullptr)
    {
        ImGui::Text("Scene is not opened");
        ImGui::End();
        return;
    }

    if (game->GetActorContext()->IsGameMode())
    {
        if (ImGui::Button("Stop"))
        {
            game->StopGame();
        }
    }
    else
    {
        if (ImGui::Button("Play"))
        {
            currentSceneActor = nullptr;
            game->StartGame();
        }
    }

    viewport->UpdateSize();
    ImGui::Image(game->GetSceneRenderer()->GetSceneResourceView(), viewport->GetSize());

    ImGui::End();
}

void EditorWindowGameViewport::renderSceneHierarchy()
{
    // Don't show additional windows if no scene is selected currently
    if (game->GetActorContext()->IsGameMode() || game->GetCurrentScene() == nullptr) return;

    updateScene();

    ImGui::Begin("Scene Hierarchy");

    ImGui::Text(currentScene->GetSceneAssetInfo()->GetName().c_str());

    ImGui::SameLine();
    if (ImGui::Button("Save"))
    {
        auto sceneAssetNode = currentScene->GetSceneAssetInfo()->GetAssetNode();
        editor->GetContext()->GetAssetManager()->SaveAsset(sceneAssetNode);
    }

    /* ImGui::SameLine();
    if (ImGui::Button("Add Room"))
    {
        currentSceneRoom = currentScene->CreateNewRoom();
    }*/

    ImGui::SameLine();
    if (ImGui::Button("Add Actor"))
    {
        updateCurrentActor(currentScene->CreateNewActorInfo());
    }

    ImGui::Separator();

    drawSceneHierarchy();

    ImGui::Separator();

    ImGui::Text("Camera Transform");
    if (paramDrawerCameraTransform->Draw())
    {
        currentScene->UpdateCameraTransform();
    }

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
    if (game->GetActorContext()->IsGameMode() || currentSceneActor == nullptr) return;

    ImGui::Begin("Actor Inspector");

    ImGui::PushItemWidth(180);

    ImGui::Text("Actor name: ");
    ImGui::InputText("##0", sceneActorName.data(), 24);
    if (ImGui::IsItemDeactivatedAfterEdit())
        currentSceneActor->SetName(sceneActorName.c_str());
    ImGui::Separator();
    ImGui::PopItemWidth();

    if (paramDrawerActorTransform->Draw())
    {
        if (currentSceneActor->GetActor() != nullptr)
        {
            currentSceneActor->GetActor()->UpdateTransform(currentSceneActor->GetParamTransform()->Get());
        }
    }
    if (paramDrawerActorAsset->Draw())
    {
        currentScene->DeleteActorFromScene(currentSceneActor);
        currentScene->CreateActorOnScene(currentSceneActor);
    }

    ImGui::End();
}

void EditorWindowGameViewport::updateScene()
{
    if (currentScene != game->GetCurrentScene())
    {
        currentScene = game->GetCurrentScene();
        updateCurrentActor(nullptr);
        delete paramDrawerCameraTransform;
        paramDrawerCameraTransform = nullptr;

        if (currentScene == nullptr) return;

        paramDrawerCameraTransform = new EditorParamDrawerTransform(
            0, "Camera Transform", currentScene->GetSceneAssetInfo()->GetCameraTransformParam());
    }
}

void EditorWindowGameViewport::updateCurrentActor(SceneActorInfo* actorInfo)
{
    currentSceneActor = actorInfo;

    delete paramDrawerActorTransform;
    paramDrawerActorTransform = nullptr;
    delete paramDrawerActorAsset;
    paramDrawerActorAsset = nullptr;

    if (currentSceneActor == nullptr)
        return;

    sceneActorName = currentSceneActor->GetName();
    sceneActorName.resize(24);

    paramDrawerActorTransform = new EditorParamDrawerTransform(1, "Transform",
        currentSceneActor->GetParamTransform());

    paramDrawerActorAsset = new EditorParamDrawerAsset(editor, paramDrawerActorTransform->GetRequiredIndexCount()+1,
        "Actor Asset", currentSceneActor->GetParamAsset());
}

void EditorWindowGameViewport::drawSceneHierarchy()
{
    /*for (SceneRoom* room : currentScene->GetActors())
    {
        drawSceneHierarchyRoom(room);
    }*/

    for (auto actorInfo : currentScene->GetSceneAssetInfo()->GetActorInfoList())
    {
        drawSceneHierarchyActor(actorInfo);
    }
}

/*
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
*/

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
        updateCurrentActor(actorInfo);
    }

    drawActorContextMenu(actorInfo);
}

void EditorWindowGameViewport::drawRoomContextMenu(SceneRoom* room)
{
    if (ImGui::BeginPopupContextItem())
    {

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

        if (ImGui::Selectable("Delete"))
        {
            currentScene->DeleteActorInfo(currentSceneActor);

            if (currentSceneActor == actorInfo)
            {
                currentSceneActor = nullptr;
            }
        }

        ImGui::EndPopup();
    }
}
