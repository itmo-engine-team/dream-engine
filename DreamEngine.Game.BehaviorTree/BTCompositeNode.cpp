#include "BTCompositeNode.h"

BTCompositeNode::BTCompositeNode(BTGameNode* parentNode) : BTGameNode(parentNode)
{
    childrenCount = 0;
}

void BTCompositeNode::SetChildren(std::vector<BTGameNode*> childrenNodes)
{
    children = childrenNodes;
    childrenCount = childrenNodes.size();
}

std::vector<BTGameNode*> BTCompositeNode::GetChildren() const
{
    return children;
}

int BTCompositeNode::GetChildrenCount() const
{
    return childrenCount;
}
