#pragma once

#include "BTGameNode.h"

class BTGameNodeRoot : public BTGameNode
{

protected:

    BTGameNode* child;

public:

    BTGameNodeRoot();

    void SetChild(BTGameNode* childNode);
    BTGameNode* GetChild();

    bool Run() override;

private:

    using BTGameNode::SetParent;

};

