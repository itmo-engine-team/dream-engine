#pragma once

class BehaviorTreeGame;
class BTGameNodeWithChild;

class BTGameNode
{

public:

    BTGameNode() = delete;
    BTGameNode(BehaviorTreeGame* behaviorTree) ;
    BTGameNode(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree);
    
    virtual ~BTGameNode() = default;

    virtual bool Run() = 0;

    void SetParent(BTGameNodeWithChild* parentNode);

    BTGameNodeWithChild* GetParent() const;
    BehaviorTreeGame* GetBehaviorTree() const;

protected:

    BTGameNodeWithChild* parent;
    BehaviorTreeGame* behaviorTree;
};

