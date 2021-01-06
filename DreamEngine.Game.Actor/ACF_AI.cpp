#include "ACF_AI.h"

ACF_AI::ACF_AI(ActorContext* context, Actor* actor) : ActorComponentFixed(context, actor)
{   
    behaviorTree = new BehaviorTreeGame(actor);
}

BehaviorTreeGame* ACF_AI::GetBehaviorTree()
{
    return behaviorTree;
}
