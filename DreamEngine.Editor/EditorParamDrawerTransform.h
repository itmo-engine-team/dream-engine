#pragma once

#include "EditorParamDrawer.h"
#include "ParamTransform.h"

class EditorParamDrawerTransform : public EditorParamDrawer<ParamTransform>
{

public:

    EditorParamDrawerTransform(int index, const std::string& name, BaseParam* baseParam);
    bool Draw() override;
    bool DrawPosition();
    bool DrawRotation();
    bool DrawScale();

    int GetRequiredIndexCount() override
    {
        return 9;
    }

private:

    const int BUFFER_SIZE = 6;

    // Position
    std::string inputFieldX;
    std::string inputFieldY;
    std::string inputFieldZ;
    std::string resetButtonLabel;

    std::string xPosLabel;
    std::string yPosLabel;
    std::string zPosLabel;

    // Rotation
    std::string inputFieldRotationX;
    std::string inputFieldRotationY;
    std::string inputFieldRotationZ;
    std::string resetRotationButtonLabel;

    std::string xRotationLabel;
    std::string yRotationLabel;
    std::string zRotationLabel;

    // Scale
    std::string inputFieldScaleX;
    std::string inputFieldScaleY;
    std::string inputFieldScaleZ;
    std::string resetScaleButtonLabel;

    std::string xScaleLabel;
    std::string yScaleLabel;
    std::string zScaleLabel;

};

