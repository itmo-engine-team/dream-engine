#include "BehaviorTreeGame.h"

BehaviorTreeGame::BehaviorTreeGame(BTGameNodeRoot* rootNode) : rootNode(rootNode)
{
}

bool BehaviorTreeGame::Update()
{
    bool result = rootNode->Run();
    return result; 
}

BTGameNodeRoot* BehaviorTreeGame::GetRootNode()
{
    return rootNode;
}
