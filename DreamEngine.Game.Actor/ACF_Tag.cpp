#include "ACF_Tag.h"

#include "ParamString.h"

ACF_Tag::ACF_Tag(Actor* actor) : ActorComponentFixed(actor)
{
    tag = new ParamString();
    AddParam("Tag", tag);
}

std::string ACF_Tag::GetTag()
{
    return tag->Get();
}


