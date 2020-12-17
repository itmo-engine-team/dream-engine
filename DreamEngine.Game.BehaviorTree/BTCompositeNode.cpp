#include "BTCompositeNode.h"

#include "BTGameNodeRoot.h"

BTCompositeNode::BTCompositeNode(BTCompositeNode* parentNode) : BTGameNode(parentNode)
{
    childrenCount = 0;
}

BTCompositeNode::BTCompositeNode(BTGameNodeRoot* parentNode) : BTGameNode(parentNode)
{
    childrenCount = 0;
}

void BTCompositeNode::AddChild(BTGameNode* childrenNodes)
{
    children.push_back(childrenNodes);
    childrenCount++;
}

bool BTCompositeNode::RemoveChild(BTGameNode* childNode)
{
    auto result = std::find(children.begin(), children.end(), childNode);
    if (result == std::end(children))
        return false;

    children.erase(result);
    childrenCount--;
    return true;
}

bool BTCompositeNode::SwapChildren(BTGameNode* childNode1, BTGameNode* childNode2)
{
    auto iterator1 = std::find(children.begin(), children.end(), childNode1);
    auto iterator2 = std::find(children.begin(), children.end(), childNode2);

    if (iterator1 == std::end(children) || iterator2 == std::end(children))
        return false;

    const ptrdiff_t childIndex1 = std::distance(children.begin(), iterator1);
    const ptrdiff_t childIndex2 = std::distance(children.begin(), iterator2);

    children.at(childIndex1) = childNode2;
    children.at(childIndex2) = childNode1;
    return true;
}

std::vector<BTGameNode*> BTCompositeNode::GetChildren() const
{
    return children;
}

int BTCompositeNode::GetChildrenCount() const
{
    return childrenCount;
}
