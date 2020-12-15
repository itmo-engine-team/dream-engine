#include "BTGameNode.h"

BTGameNode::BTGameNode(BTGameNode* parentNode) : parent(parentNode)
{
}

void BTGameNode::SetParent(BTGameNode* parentNode) 
{
    parent = parentNode;
}

BTGameNode* BTGameNode::GetParent() const
{
    return parent;
}