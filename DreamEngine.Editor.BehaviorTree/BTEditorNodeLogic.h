#pragma once

#include "BTEditorNode.h"

class BTEditorNodeLogic : public BTEditorNode
{

public:

    BTEditorNodeLogic();

    bool CanHaveParent() override;
    bool CanHaveChild() override;
    bool CanHaveChildren() override;

protected:

    Json toJson() override;
    void fromJson(Json json) override;

};

