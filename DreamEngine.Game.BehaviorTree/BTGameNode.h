#pragma once

class BTGameNodeRoot;
class BTCompositeNode;

class BTGameNode
{

protected:

    BTGameNode* parent;

public:

    BTGameNode() = default;
    BTGameNode(BTGameNodeRoot* parentNode);
    BTGameNode(BTCompositeNode* parentNode);
    
    virtual ~BTGameNode() = default;

    virtual bool Run() = 0;

    void SetParent(BTGameNode* parentNode);

    BTGameNode* GetParent() const;

};

