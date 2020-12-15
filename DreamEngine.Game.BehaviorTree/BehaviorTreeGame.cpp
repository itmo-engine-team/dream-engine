#include "BehaviorTreeGame.h"

BehaviorTreeGame::BehaviorTreeGame(BTGameNodeRoot* rootNode) : rootNode(rootNode)
{
}

void BehaviorTreeGame::Update()
{
    rootNode->Run();
}
