#include "BTGameNode.h"

BTGameNode::BTGameNode(BTGameNode* parentNode) : parent(parentNode)
{
}

//BTGameNode::BTGameNode(BTGameNode* parentNode, std::vector<BTGameNode*> childrenNodes)
//    : parent(parentNode), children(childrenNodes), childrenCount(childrenNodes.size())
//{
//}

void BTGameNode::SetParent(BTGameNode* parentNode) 
{
    parent = parentNode;
}

//void BTGameNode::SetChildren(std::vector<BTGameNode*> childrenNodes)
//{
//    children = childrenNodes;
//    childrenCount = children.size();
//}

BTGameNode* BTGameNode::GetParent() const
{
    return parent;
}

//std::vector<BTGameNode*> BTGameNode::GetChildren() const
//{
//    return children;
//}
//
//int BTGameNode::GetChildrenCount() const
//{
//    return childrenCount;
//}
