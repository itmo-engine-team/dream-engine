#pragma once

#include "BTCompositeNode.h"

class BTGameNodeSelector : public BTCompositeNode
{

public:

    BTGameNodeSelector() = delete;
    BTGameNodeSelector(BTCompositeNode* parentNode);
    BTGameNodeSelector(BTGameNodeRoot* parentNode);

    bool Run() override;

};

