#pragma once

#include "BTEditorNode.h"
#include "BTEditorNodeComposite.h"
#include "BTEditorNodeLogic.h"
#include "BTEditorNodeRoot.h"

class BTEditorNodeFactory
{

public:

    static BTEditorNode* Create(BTNodeType type)
    {
        switch (type)
        {
            case BTNodeType::Root:
                return new BTEditorNodeRoot();
            case BTNodeType::Composite:
                return new BTEditorNodeComposite();
            case BTNodeType::Logic:
                return new BTEditorNodeLogic();
            default:
                return nullptr;
        }
    }

};
