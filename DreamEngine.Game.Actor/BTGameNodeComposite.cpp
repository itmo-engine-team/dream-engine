#include "BTGameNodeComposite.h"

#include "BTGameNodeRoot.h"

BTGameNodeComposite::BTGameNodeComposite(BTGameNodeComposite* parentNode) : BTGameNode(parentNode)
{
}

BTGameNodeComposite::BTGameNodeComposite(BTGameNodeRoot* parentNode) : BTGameNode(parentNode)
{
}

void BTGameNodeComposite::AddChild(BTGameNode* childNod)
{
    children.push_back(childNod);
}

bool BTGameNodeComposite::RemoveChild(BTGameNode* childNode)
{
    auto result = std::find(children.begin(), children.end(), childNode);
    if (result == std::end(children))
        return false;

    children.erase(result);
    return true;
}

bool BTGameNodeComposite::SwapChildren(BTGameNode* childNode1, BTGameNode* childNode2)
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

std::vector<BTGameNode*> BTGameNodeComposite::GetChildren() const
{
    return children;
}