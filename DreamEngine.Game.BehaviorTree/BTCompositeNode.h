#pragma once

#include "BTGameNode.h"
#include <vector>

class BTCompositeNode : public BTGameNode
{

protected:

    std::vector<BTGameNode*> children;
    int childrenCount;

public:

    BTCompositeNode(BTGameNode* parentNode);

    void SetChildren(std::vector<BTGameNode*> childrenNodes);

    std::vector<BTGameNode*> GetChildren() const;
    int GetChildrenCount() const;
};

