#pragma once

class BTGameNodeRoot;
class BTGameNodeComposite;

class BTGameNode
{

public:

    BTGameNode() = default;
    BTGameNode(BTGameNodeRoot* parentNode);
    BTGameNode(BTGameNodeComposite* parentNode);
    
    virtual ~BTGameNode() = default;

    virtual bool Run() = 0;

    void SetParent(BTGameNode* parentNode);

    BTGameNode* GetParent() const;

protected:

    BTGameNode* parent;
};

