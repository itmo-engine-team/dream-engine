#pragma once

#include "BTGameNode.h"

class BTGameNodeLogic : public BTGameNode
{

public:

    //TODO: delete after all tests end
    bool TestCheckResult = false;

    BTGameNodeLogic() = delete;
    BTGameNodeLogic(BTGameNodeRoot* parentNode);
    BTGameNodeLogic(BTGameNodeComposite* parentNode);

    bool Run() override;

};

