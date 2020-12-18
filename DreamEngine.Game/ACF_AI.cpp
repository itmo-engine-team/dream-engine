#include "ACF_AI.h"

ACF_AI::ACF_AI(Game* game, Actor* actor) : ActorComponent(game, actor)
{   
    behaviorTree = new BehaviorTreeGame();
}

BehaviorTreeGame* ACF_AI::GetBehaviorTree()
{
    return behaviorTree;
}
