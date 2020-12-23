#pragma once

#include <vector>

class SceneRoomInfo;
class Actor;
class ActorContext;

class SceneRoom
{

public:

    SceneRoom(ActorContext* context, SceneRoomInfo* roomInfo);
    ~SceneRoom();

    void AddActor(Actor* actor);

    const std::vector<Actor*>& GetActors() const;

protected:

    std::vector<Actor*> actors;

};

