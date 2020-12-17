#include "BTGameNodeRoot.h"

BTGameNodeRoot::BTGameNodeRoot()
{
    parent = nullptr;
    child = nullptr;
}

void BTGameNodeRoot::SetChild(BTGameNode* childNode)
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

