#pragma once

#include "EditorParamDrawer.h"
#include "ParamTransform.h"

class EditorParamDrawerTransform : public EditorParamDrawer<ParamTransform>
{

public:

    EditorParamDrawerTransform(int index, const std::string& name, BaseParam* baseParam);
    bool Draw() override;

    int GetRequiredIndexCount() override
    {
        return 3;
    }

private:

    std::string inputFieldX;
    std::string inputFieldY;
    std::string inputFieldZ;
    std::string resetButtonLabel;

    std::string xPosLabel;
    std::string yPosLabel;
    std::string zPosLabel;

    bool isChanged;
};

