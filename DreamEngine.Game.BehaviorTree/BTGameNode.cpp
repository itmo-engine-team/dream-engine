#include "BTGameNode.h"

#include "BTGameNodeRoot.h"
#include "BTCompositeNode.h"

BTGameNode::BTGameNode(BTGameNodeRoot* parentNode) : parent(parentNode)
{
    parentNode->SetChild(this);
}

BTGameNode::BTGameNode(BTCompositeNode* parentNode) : parent(parentNode)
{
    parentNode->AddChild(this);
}

void BTGameNode::SetParent(BTGameNode* parentNode) 
{
    parent = parentNode;
}

BTGameNode* BTGameNode::GetParent() const
{
    return parent;
}