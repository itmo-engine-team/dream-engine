#pragma once

#include <vector>

class BTGameNode
{

protected:

    BTGameNode* parents;
    std::vector<BTGameNode*> children;
    int childrenCount;

public:

    virtual bool Run() = 0;
};

