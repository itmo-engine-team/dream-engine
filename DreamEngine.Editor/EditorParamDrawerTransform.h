#pragma once

#include "EditorParamDrawer.h"
#include "ParamTransform.h"

class EditorParamDrawerTransform : public EditorParamDrawer<ParamTransform>
{

public:

    EditorParamDrawerTransform(int index, const std::string& name, BaseParam* baseParam);
    bool Draw() override;

private:

    std::string inputFieldX;
    std::string inputFieldY;
    std::string inputFieldZ;
    std::string buttonLabel;

    std::string xPosLabel;
    std::string yPosLabel;
    std::string zPosLabel;
};

