#pragma once

class BTGameNode
{

protected:

    BTGameNode* parent;

public:

    BTGameNode(BTGameNode* parentNode);
    virtual ~BTGameNode() = default;

    virtual bool Run() = 0;

    void SetParent(BTGameNode* parentNode);

    BTGameNode* GetParent() const;

};

