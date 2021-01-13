#pragma once

#include "BTGameNodeWithChild.h"

class BTGameNodeRoot : public BTGameNodeWithChild
{

public:

    BTGameNodeRoot() = delete;

    void AddChildNode(BTGameNode* childNode) override;
    BTGameNode* GetChild();

    void RemoveChild();

    bool Run() override;

protected:

    friend class BehaviorTreeGame;
    BTGameNodeRoot(BehaviorTreeGame* behaviorTree);

private:

    using BTGameNode::SetParent;

    BTGameNode* child;
};

