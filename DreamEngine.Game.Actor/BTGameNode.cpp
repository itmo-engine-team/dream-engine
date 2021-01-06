#include "BTGameNode.h"

#include "BTGameNodeRoot.h"
#include "BTGameNodeComposite.h"

BTGameNode::BTGameNode(BTGameNodeRoot* parentNode) : parent(parentNode)
{
    parentNode->SetChild(this);
}

BTGameNode::BTGameNode(BTGameNodeComposite* parentNode) : parent(parentNode)
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