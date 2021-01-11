#pragma once

#include <vector>
#include <string>

class SceneRoomInfo;
class Actor;
class ActorContext;

class SceneRoom
{

public:
    
    SceneRoom(ActorContext* context, SceneRoomInfo* roomInfo);
    ~SceneRoom();

    SceneRoomInfo* GetRoomInfo() const;

    /*void CreateActor();
    const std::vector<Actor*>& GetActors() const;*/

protected:

    ActorContext* context;
    SceneRoomInfo* roomInfo;

    //std::vector<Actor*> actors;

};

