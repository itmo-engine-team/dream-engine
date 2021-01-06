#pragma once

#include "BTGameNode.h"
#include <vector>

class BTGameNodeRoot;

class BTGameNodeComposite : public BTGameNode
{

public:

    BTGameNodeComposite() = delete;
    BTGameNodeComposite(BTGameNodeComposite* parentNode);
    BTGameNodeComposite(BTGameNodeRoot* parentNode);

    void AddChild(BTGameNode* childNod);
    bool RemoveChild(BTGameNode* childNode);
    bool SwapChildren(BTGameNode* childNode1, BTGameNode* childNode2);

    std::vector<BTGameNode*> GetChildren() const;

protected:

    std::vector<BTGameNode*> children;
};

