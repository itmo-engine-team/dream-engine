#include "BTGameNode.h"

#include "BTGameNodeRoot.h"
#include "BTGameNodeComposite.h"
#include "BehaviorTreeGame.h"

BTGameNode::BTGameNode(BehaviorTreeGame* behaviorTree) : behaviorTree(behaviorTree)
{
}

BTGameNode::BTGameNode(BTGameNodeRoot* parentNode, BehaviorTreeGame* behaviorTree) : parent(parentNode), behaviorTree(behaviorTree)
{
    parentNode->SetChild(this);
}

BTGameNode::BTGameNode(BTGameNodeComposite* parentNode, BehaviorTreeGame* behaviorTree) : parent(parentNode), behaviorTree(behaviorTree)
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

BehaviorTreeGame* BTGameNode::GetBehaviorTree() const
{
    return behaviorTree;
}
