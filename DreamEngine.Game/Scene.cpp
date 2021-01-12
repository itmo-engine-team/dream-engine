#include "Scene.h"

#include "SceneAssetInfo.h"
#include "SceneRoomInfo.h"
#include "ActorContext.h"
#include "ActorFactory.h"
#include "ParamAsset.h"
#include "ActorAssetInfo.h"

Scene::Scene(ActorContext* context, SceneAssetInfo* sceneInfo) : context(context), sceneInfo(sceneInfo)
{
    // Check if scene room is new
    if (sceneInfo == nullptr) return;

    for (SceneActorInfo* const actorInfo : sceneInfo->GetActorInfoList())
    {
        if (actorInfo->GetParamAsset()->IsDefault()) return;

        auto actorAsset = dynamic_cast<ActorAssetInfo*>(context->GetAssetManager()->GetAssetByType(
            AssetType::Actor, actorInfo->GetParamAsset()->Get()));

        if (actorAsset == nullptr) return;


        auto actor = ActorFactory::Create(context, actorAsset->GetActorType());
        actor->UpdateTransform(actorInfo->GetParamTransform()->Get());
        actorInfo->SetActor(actor);
        actors.push_back(actor);

    }

   /* for (SceneRoomInfo* roomInfo : sceneInfo->GetRoomInfoList())
    {
        rooms.push_back(new SceneRoom(context, roomInfo));
    }

    currentRoom = rooms.empty() ? nullptr : rooms[0];*/
}

Scene::~Scene()
{
    for (Actor* actor : actors)
    {
        delete actor;
    }

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

SceneActorInfo* Scene::CreateActor()
{
    SceneActorInfo* actorInfo = new SceneActorInfo();
    actorInfo->SetName("Actor " + std::to_string(actors.size()));
    sceneInfo->AddActorInfo(actorInfo);
    
    return actorInfo;
}

const std::vector<Actor*>& Scene::GetActors() const
{
    return actors;
}
