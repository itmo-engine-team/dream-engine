#pragma once

#include "BTEditorNode.h"

class BTEditorNodeComposite : public BTEditorNode
{

public:

    BTEditorNodeComposite();

    BTNodeCompositeType GetCompositeType() const;
    void SetCompositeType(BTNodeCompositeType compositeType);

    bool CanHaveParent() override;
    bool CanHaveChild() override;
    bool CanHaveChildren() override;

protected:

    Json toJson() override;
    void fromJson(Json json) override;

private:

    BTNodeCompositeType compositeType;

};

