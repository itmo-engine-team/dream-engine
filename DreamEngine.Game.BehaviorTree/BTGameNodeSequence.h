#pragma once

#include "BTGameNodeComposite.h"

class BTGameNodeSequence : public BTGameNodeComposite
{

public:

    BTGameNodeSequence() = delete;
    BTGameNodeSequence(BTGameNodeRoot* parentNode);
    BTGameNodeSequence(BTGameNodeComposite* parentNode);

    bool Run() override;
};

