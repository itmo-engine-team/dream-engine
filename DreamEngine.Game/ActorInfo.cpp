#include "ActorInfo.h"

ActorInfo::ActorInfo(ActorType type) : type(type)
{
    
}

ActorType ActorInfo::GetType() const
{
    return type;
}
