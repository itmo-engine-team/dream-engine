#pragma once

#include "BTEditorNode.h"

class BTEditorNodeFactory;
class BehaviorTreeEditor;

class BTEditorNodeRoot : public BTEditorNode
{

public:

    bool CanHaveParent() override;
    bool CanHaveChild() override;
    bool CanHaveChildren() override;

protected:

    friend BehaviorTreeEditor;
    friend BTEditorNodeFactory;
    BTEditorNodeRoot();

};

