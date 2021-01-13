#pragma once

#include "EditorParamDrawer.h"
#include "ParamInt.h"

class EditorParamDrawerInt : public EditorParamDrawer<ParamInt>
{

public:

    EditorParamDrawerInt(int index, const std::string& name, BaseParam* baseParam);

    bool Draw() override;

private:

    std::string inputField;
    std::string inputFieldLabel;
    std::string resetButtonLabel;

};

