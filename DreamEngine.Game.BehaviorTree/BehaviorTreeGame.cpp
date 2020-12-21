#include "BehaviorTreeGame.h"

BehaviorTreeGame::BehaviorTreeGame()
{
    rootNode = new BTGameNodeRoot();
}

bool BehaviorTreeGame::Update()
{
    return rootNode->Run();
}

BTGameNodeRoot* BehaviorTreeGame::GetRootNode()
{
    return rootNode;
}
