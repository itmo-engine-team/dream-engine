#pragma once

#include "BTGameNodeWithChild.h"

class BTGameNodeRoot : public BTGameNodeWithChild
{

protected:

    friend class BehaviorTreeGame;
    BTGameNodeRoot() = delete;
    BTGameNodeRoot(BehaviorTreeGame* behaviorTree);

public:

    void AddChildNode(BTGameNode* childNode) override;
    BTGameNode* GetChild();

    void RemoveChild();

    bool Run() override;

private:

    using BTGameNode::SetParent;

    BTGameNode* child;

};

