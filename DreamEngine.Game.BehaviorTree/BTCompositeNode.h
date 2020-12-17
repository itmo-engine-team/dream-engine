#pragma once

#include "BTGameNode.h"
#include <vector>

class BTGameNodeRoot;

class BTCompositeNode : public BTGameNode
{

protected:

    std::vector<BTGameNode*> children;
    int childrenCount;

public:

    BTCompositeNode() = delete;
    BTCompositeNode(BTCompositeNode* parentNode);
    BTCompositeNode(BTGameNodeRoot* parentNode);

    void AddChild(BTGameNode* childrenNodes);
    bool RemoveChild(BTGameNode* childNode);
    bool SwapChildren(BTGameNode* childNode1, BTGameNode* childNode2);

    std::vector<BTGameNode*> GetChildren() const;
    int GetChildrenCount() const;

    int iterator = 0;
};

