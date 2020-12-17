#pragma once

#include "BTCompositeNode.h"

class BTGameNodeSequence : public BTCompositeNode
{

public:

    BTGameNodeSequence() = delete;
    BTGameNodeSequence(BTGameNodeRoot* parentNode);
    BTGameNodeSequence(BTCompositeNode* parentNode);

    bool Run() override;
};

