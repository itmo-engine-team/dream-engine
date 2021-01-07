#pragma once

#include <vector>
#include "EditorParamDrawer.h"

class ParamExtender;
class ParamAsset;
class ParamInt;
class BaseParam;

class EditorParamViewer
{

public:

    EditorParamViewer(ParamExtender* paramExtender);
    ~EditorParamViewer();

    BaseParam* Draw();

private:

    ParamExtender* paramExtender;
    std::vector<EditorParamDrawerBase*> paramDrawers;

    EditorParamDrawerBase* createParamDrawer(const std::string& name, BaseParam* baseParam);

};

