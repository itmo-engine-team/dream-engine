#pragma once

#include "EditorParamDrawer.h"
#include "ParamString.h"

class EditorParamDrawerString : public EditorParamDrawer<ParamString>
{

public:

    EditorParamDrawerString(int index, const std::string& name, BaseParam* baseParam);

    bool Draw() override;

private:

    std::string inputField;
    std::string inputFieldLabel;
    std::string resetButtonLabel;

};