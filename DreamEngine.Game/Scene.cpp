#include "Scene.h"

#include "SceneAssetInfo.h"
#include "SceneRoomInfo.h"
#include "ActorContext.h"
#include "ActorFactory.h"
#include "ParamAsset.h"
#include "ActorAssetInfo.h"
#include "ActorComponentFactory.h"
#include "GameAssetManager.h"

Scene::Scene(ActorContext* context, SceneAssetInfo* sceneInfo)
    : context(context), sceneInfo(sceneInfo)
{
    // Check if scene room is new
    if (sceneInfo == nullptr) return;

    for (SceneActorInfo* const actorInfo : sceneInfo->GetActorInfoList())
    {       
        CreateActorOnScene(actorInfo);
    }

   /* for (SceneRoomInfo* roomInfo : sceneInfo->GetRoomInfoList())
    {
        rooms.push_back(new SceneRoom(context, roomInfo));
    }

    currentRoom = rooms.empty() ? nullptr : rooms[0];*/
}

Scene::~Scene()
{
    /*for (SceneRoom* room : rooms)
    {
        delete room;
    }*/
}

SceneAssetInfo* Scene::GetSceneAssetInfo() const
{
    return sceneInfo;
}

//SceneRoom* Scene::CreateNewRoom()
//{
//    SceneRoomInfo* roomInfo = new SceneRoomInfo();
//    roomInfo->SetName("Room " + std::to_string(rooms.size()));
//    sceneInfo->AddRoomInfo(roomInfo);
//
//    SceneRoom* room = new SceneRoom(context, roomInfo);
//    rooms.push_back(room);
//    return room;
//}

//SceneRoom* Scene::GetCurrentRoom() const
//{
//    return currentRoom;
//}

/*std::vector<SceneRoom*> Scene::GetRoomList() const
{
    return rooms;
}*/

SceneActorInfo* Scene::CreateNewActorInfo()
{
    SceneActorInfo* actorInfo = new SceneActorInfo();
    actorInfo->SetName("Actor " + std::to_string(context->GetGameAssetManager()->GetActors().size()));
    sceneInfo->AddActorInfo(actorInfo);
    
    return actorInfo;
}

void Scene::CreateActorOnScene(SceneActorInfo* actorInfo)
{
    if (actorInfo->GetParamAsset()->IsDefault()) return;

    auto actorAsset = dynamic_cast<ActorAssetInfo*>(context->GetAssetManager()->GetAssetByType(
        AssetType::Actor, actorInfo->GetParamAsset()->Get()));

    if (actorAsset == nullptr) return;

    auto actor = CreateActorFromAsset(actorAsset);
    actor->UpdateTransform(actorInfo->GetParamTransform()->Get());
    context->GetGameAssetManager()->AddActor(actor);
    actorInfo->SetActor(actor);
}

void Scene::DeleteActorFromScene(SceneActorInfo* actorInfo)
{
    context->GetGameAssetManager()->DeleteActor(actorInfo->GetActor());
    actorInfo->SetActor(nullptr);
}

Actor* Scene::CreateActorFromAsset(ActorAssetInfo* actorAssetInfo)
{
    auto actor = ActorFactory::Create(context, actorAssetInfo->GetActorType());

    for (auto sceneComponentInfo : actorAssetInfo->GetSceneComponents())
    {
        auto sceneComponent = ActorComponentFactory::CreateSceneComponent(actor, sceneComponentInfo);
        actor->AddSceneComponent(sceneComponent);

        for (auto iter : sceneComponentInfo->GetParamExtender()->GetParamMap())
        {
            sceneComponent->UpdateParam(iter.first, iter.second);
        }
    }

    for (auto fixedComponentInfo : actorAssetInfo->GetFixedComponents())
    {
        auto fixedComponent = ActorComponentFactory::CreateFixedComponent(actor, fixedComponentInfo);
        actor->AddFixedComponent(fixedComponent);

        for (auto iter : fixedComponentInfo->GetParamExtender()->GetParamMap())
        {
            fixedComponent->UpdateParam(iter.first, iter.second);
        }
    }

    return actor;
}