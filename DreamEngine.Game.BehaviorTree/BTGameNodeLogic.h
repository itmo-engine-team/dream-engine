#pragma once

#include "BTGameNode.h"

class BTGameNodeLogic : public BTGameNode
{

public:

    BTGameNodeLogic(BTGameNode* parentNode);

    bool result = false;

    bool Run() override;

};

