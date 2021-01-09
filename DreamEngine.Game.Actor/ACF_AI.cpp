#include "ACF_AI.h"

ACF_AI::ACF_AI(Actor* actor) : ActorComponentFixed(actor)
{   
    behaviorTree = new BehaviorTreeGame(actor, nullptr);
}

BehaviorTreeGame* ACF_AI::GetBehaviorTree()
{
    return behaviorTree;
}
