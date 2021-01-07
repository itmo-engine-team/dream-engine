#pragma once

#include "BTEditorNode.h"
#include "BTNodeLogicType.h"

class BTEditorNodeLogic : public BTEditorNode
{

public:

    BTEditorNodeLogic();

    bool CanHaveParent() override;
    bool CanHaveChild() override;
    bool CanHaveChildren() override;

    BTNodeLogicType GetLogicType() const;
    void SetLogicType(BTNodeLogicType logicType);

protected:

    Json toJson() override;
    void fromJson(Json json) override;

private:

    BTNodeLogicType logicType;

};

