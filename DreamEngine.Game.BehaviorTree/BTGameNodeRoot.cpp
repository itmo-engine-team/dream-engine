#include "BTGameNodeRoot.h"

BTGameNodeRoot::BTGameNodeRoot() : BTGameNode(nullptr)
{
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

bool BTGameNodeRoot::Run()
{
   bool result =  child->Run();
   return result;
}

