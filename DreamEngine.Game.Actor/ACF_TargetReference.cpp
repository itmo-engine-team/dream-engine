#include "ACF_TargetReference.h"

ACF_TargetReference::ACF_TargetReference(Actor* actor, Actor* targetRef) : ActorComponentFixed(actor), targetRef(targetRef)
{
}

Actor* ACF_TargetReference::GetTarget()
{
    return targetRef;
}

void ACF_TargetReference::SetTarget(Actor* targetRef)
{
    this->targetRef = targetRef;
}
