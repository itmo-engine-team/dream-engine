#include "BehaviorTreeGame.h"

BehaviorTreeGame::BehaviorTreeGame()
{
    BTGameNodeRoot* root = new BTGameNodeRoot();
    rootNode = root;
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
