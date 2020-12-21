#include "SceneRoom.h"

#include "Actor.h"
#include "SceneRoomInfo.h"
#include "ActorFactory.h"

SceneRoom::SceneRoom(Game* game, SceneRoomInfo* roomInfo)
{
    for (SceneActorInfo* const actorInfo : roomInfo->GetActorInfoList())
    {
        actors.push_back(ActorFactory::Create(game, actorInfo));
    }
}

SceneRoom::~SceneRoom()
{
    for (Actor* actor : actors)
    {
        delete actor;
    }
}

void SceneRoom::AddActor(Actor* actor)
{
    actors.push_back(actor);
}

const std::vector<Actor*>& SceneRoom::GetActors() const
{
    return actors;
}
