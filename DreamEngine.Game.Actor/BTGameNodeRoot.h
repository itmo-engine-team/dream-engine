#pragma once

#include "BTGameNode.h"

class BehaviorTreeGame;

class BTGameNodeRoot : public BTGameNode
{

protected:

    friend class BehaviorTreeGame;
    BTGameNodeRoot();

public:

    void SetChild(BTGameNode* childNode);
    BTGameNode* GetChild();

    void RemoveChild();

    bool Run() override;

private:

    using BTGameNode::SetParent;

    BTGameNode* child;

};

