#include "BTGameNode.h"

BTGameNode::BTGameNode(BTGameNode* parentNode, std::vector<BTGameNode*> childrenNodes)
    : parent(parentNode), children(childrenNodes), childrenCount(childrenNodes.size())
{
}

void BTGameNode::SetParent(BTGameNode* parentNode) 
{
    parent = parentNode;
}

void BTGameNode::SetChildren(std::vector<BTGameNode*> childrenNodes)
{
    children = childrenNodes;
    childrenCount = children.size();
}

BTGameNode* BTGameNode::GetParent()
{
    return parent;
}

std::vector<BTGameNode*> BTGameNode::GetChildren()
{
    return children;
}

int BTGameNode::GetChildrenCount()
{
    return childrenCount;
}
