#include "SceneActorInfo.h"

SceneActorInfo::SceneActorInfo(ActorType type) : type(type)
{
    
}

ActorType SceneActorInfo::GetType() const
{
    return type;
}

TransformInfo* SceneActorInfo::GetTransformInfo() const
{
    return transformInfo;
}
