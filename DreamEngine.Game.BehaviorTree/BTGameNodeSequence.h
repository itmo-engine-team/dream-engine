#pragma once

#include "BTCompositeNode.h"

class BTGameNodeSequence : public BTCompositeNode
{

public:

    BTGameNodeSequence(BTGameNode* parentNode);

    bool Run() override;
};

