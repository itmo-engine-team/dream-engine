#include "BehaviorTreeGame.h"

BehaviorTreeGame::BehaviorTreeGame(Actor* actor) : actor(actor)
{
    rootNode = new BTGameNodeRoot(this);
}

bool BehaviorTreeGame::Update()
{
    return rootNode->Run();
}

BTGameNodeRoot* BehaviorTreeGame::GetRootNode()
{
    return rootNode;
}

Actor* BehaviorTreeGame::GetActor()
{
    return actor;
}
