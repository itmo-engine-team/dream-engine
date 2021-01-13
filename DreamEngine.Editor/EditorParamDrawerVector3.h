#pragma once

#include "EditorParamDrawer.h"
#include "ParamVector3.h"

class EditorParamDrawerVector3 : public EditorParamDrawer<ParamVector3>
{

public:

    EditorParamDrawerVector3(int index, const std::string& name, BaseParam* baseParam);
    bool Draw() override;

    int GetRequiredIndexCount() override
    {
        return 3;
    }

private:

    const int BUFFER_SIZE = 6;

    std::string inputFieldX;
    std::string inputFieldY;
    std::string inputFieldZ;
    std::string resetButtonLabel;

    std::string xPosLabel;
    std::string yPosLabel;
    std::string zPosLabel;

};
