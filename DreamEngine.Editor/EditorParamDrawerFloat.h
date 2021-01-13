#pragma once

#include "EditorParamDrawer.h"
#include "ParamFloat.h"

class EditorParamDrawerFloat : public EditorParamDrawer<ParamFloat>
{

public:

    EditorParamDrawerFloat(int index, const std::string& name, BaseParam* baseParam);

    bool Draw() override;

private:

    std::string inputField;
    std::string inputFieldLabel;
    std::string resetButtonLabel;

};