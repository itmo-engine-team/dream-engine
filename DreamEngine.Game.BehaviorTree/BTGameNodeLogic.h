#pragma once

#include "BTGameNode.h"

class BTGameNodeLogic : public BTGameNode
{

public:

    BTGameNodeLogic() = delete;
    BTGameNodeLogic(BTGameNodeRoot* parentNode);
    BTGameNodeLogic(BTCompositeNode* parentNode);

    bool result = false;

    bool Run() override;

};

