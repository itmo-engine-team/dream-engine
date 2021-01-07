#include "BTGameNode.h"

#include "BTGameNodeWithChild.h"
#include "BehaviorTreeGame.h"

BTGameNode::BTGameNode(BehaviorTreeGame* behaviorTree) : behaviorTree(behaviorTree)
{
}

BTGameNode::BTGameNode(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree) : parent(parentNode), behaviorTree(behaviorTree)
{
    parentNode->AddChildNode(this);
}


void BTGameNode::SetParent(BTGameNodeWithChild* parentNode)
{
    parent = parentNode;
}

BTGameNodeWithChild* BTGameNode::GetParent() const
{
    return parent;
}

BehaviorTreeGame* BTGameNode::GetBehaviorTree() const
{
    return behaviorTree;
}
