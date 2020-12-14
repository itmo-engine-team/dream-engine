#pragma once

#include <vector>

class BTGameNode
{

protected:

    BTGameNode* parent;
    std::vector<BTGameNode*> children;
    int childrenCount;

public:

    BTGameNode(BTGameNode* parentNode, std::vector<BTGameNode*> childrenNodes);
    virtual ~BTGameNode() = default;

    virtual bool Run() = 0;

    virtual void SetParent(BTGameNode* parentNode);
    void SetChildren(std::vector<BTGameNode*> childrenNodes);

    virtual BTGameNode* GetParent();
    std::vector<BTGameNode*> GetChildren();
    int GetChildrenCount();

};

