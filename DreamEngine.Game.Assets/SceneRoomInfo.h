#pragma once

#include "Serializable.h"

class SceneActorInfo;

class SceneRoomInfo : Serializable
{

public:

    SceneRoomInfo();

    const std::string& GetName() const;
    void SetName(const std::string& name);

    const std::vector<SceneActorInfo*>& GetActorInfoList() const;

protected:

    friend class SceneAssetInfo;

    Json toJson() override;
    void fromJson(Json json) override;

private:

    std::string name;
    std::vector<SceneActorInfo*> actorInfoList;

};

