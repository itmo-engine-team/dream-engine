#pragma once

#include "BTEditorNode.h"
#include "BTEditorNodeComposite.h"
#include "BTEditorNodeLogic.h"

class BTEditorNodeFactory
{

public:

    static BTEditorNode* Create(BTNodeType type)
    {
        switch (type)
        {
            case BTNodeType::Composite:
                return new BTEditorNodeComposite();
            case BTNodeType::Logic:
                return new BTEditorNodeLogic();
            default:
                return nullptr;
        }
    }

};
