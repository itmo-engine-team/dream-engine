#pragma once

class BehaviorTreeGame;
class BTGameNodeWithChild;

class BTGameNode
{

public:

    BTGameNode() = delete;
    
    virtual ~BTGameNode() = default;

    virtual bool Run() = 0;

    void SetParent(BTGameNodeWithChild* parentNode);

    BTGameNodeWithChild* GetParent() const;
    BehaviorTreeGame* GetBehaviorTree() const;

protected:

    BTGameNode(BehaviorTreeGame* behaviorTree);
    BTGameNode(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree);

    BTGameNodeWithChild* parent;
    BehaviorTreeGame* behaviorTree;
};

