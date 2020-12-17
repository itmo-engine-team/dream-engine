#pragma once

#include "BTGameNodeComposite.h"

class BTGameNodeSelector : public BTGameNodeComposite
{

public:

    BTGameNodeSelector() = delete;
    BTGameNodeSelector(BTGameNodeComposite* parentNode);
    BTGameNodeSelector(BTGameNodeRoot* parentNode);

    bool Run() override;

};

