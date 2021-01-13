#pragma once

#include "EditorParamDrawer.h"
#include "ParamBool.h"

class EditorParamDrawerBool : public EditorParamDrawer<ParamBool>
{

public:

    EditorParamDrawerBool(int index, const std::string& name, BaseParam* baseParam);

    bool Draw() override;

private:

    bool paramCheckBox;

    std::string checkboxLabel;
    std::string resetButtonLabel;

};