#include "BTGameNodeRoot.h"

BTGameNodeRoot::BTGameNodeRoot(BehaviorTreeGame* behaviorTree) : BTGameNodeWithChild(behaviorTree)
{
    parent = nullptr;
    child = nullptr;
}

void BTGameNodeRoot::AddChildNode(BTGameNode* childNode)
{
    child = childNode;
}

BTGameNode* BTGameNodeRoot::GetChild()
{
    return child;
}

void BTGameNodeRoot::RemoveChild()
{
    child = nullptr;
}

bool BTGameNodeRoot::Run()
{
    if (child == nullptr)
        return false;

    return child->Run();
}

