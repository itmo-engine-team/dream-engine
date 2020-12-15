#pragma once

#include "BTCompositeNode.h"

class BTGameNodeSelector : public BTCompositeNode
{

public:

    BTGameNodeSelector(BTGameNode* parentNode);

    bool Run() override;

};

