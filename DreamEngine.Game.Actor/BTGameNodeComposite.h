#pragma once

#include <vector>

#include "BTGameNodeWithChild.h"

class BehaviorTreeGame;

class BTGameNodeComposite : public BTGameNodeWithChild
{

public:

    BTGameNodeComposite() = delete;
    BTGameNodeComposite(BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree);

    void AddChildNode(BTGameNode* childNod) override;
    bool RemoveChild(BTGameNode* childNode);
    bool SwapChildren(BTGameNode* childNode1, BTGameNode* childNode2);

    std::vector<BTGameNode*> GetChildren() const;

protected:

    std::vector<BTGameNode*> children;
};

