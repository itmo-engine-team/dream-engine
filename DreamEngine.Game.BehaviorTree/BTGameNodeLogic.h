#pragma once

#include "BTGameNode.h"

class BTGameNodeLogic : public BTGameNode
{

public:

    BTGameNodeLogic() = delete;
    BTGameNodeLogic(BTGameNodeRoot* parentNode);
    BTGameNodeLogic(BTGameNodeComposite* parentNode);

    //TODO: delete after all tests end
    bool TestCheckResult = false;

    bool Run() override;

};

