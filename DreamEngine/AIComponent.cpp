#include "AIComponent.h"

AIComponent::AIComponent(Game* game, Actor* actor) : ActorComponent(game, actor)
{   
    behaviorTree = new BehaviorTreeGame();
}

BehaviorTreeGame* AIComponent::GetBehaviorTree()
{
    return behaviorTree;
}
