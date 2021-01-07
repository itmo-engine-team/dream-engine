#pragma once

class BehaviorTreeGame;
class BTGameNodeRoot;
class BTGameNodeComposite;

class BTGameNode
{

public:

    BTGameNode() = delete;
    BTGameNode(BehaviorTreeGame* behaviorTree) ;
    BTGameNode(BTGameNodeRoot* parentNode, BehaviorTreeGame* behaviorTree);
    BTGameNode(BTGameNodeComposite* parentNode, BehaviorTreeGame* behaviorTree);
    
    virtual ~BTGameNode() = default;

    virtual bool Run() = 0;

    void SetParent(BTGameNode* parentNode);

    BTGameNode* GetParent() const;
    BehaviorTreeGame* GetBehaviorTree() const;

protected:

    BTGameNode* parent;
    BehaviorTreeGame* behaviorTree;
};

