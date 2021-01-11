#pragma once

#include <vector>
#include "EditorParamDrawer.h"

class Editor;
class ParamExtender;
class ParamAsset;
class ParamInt;
class ParamTransform;
class BaseParam;

class EditorParamViewer
{

public:

    EditorParamViewer(Editor* editor, ParamExtender* paramExtender, int index = 0);
    ~EditorParamViewer();

    BaseParam* Draw();

private:

    Editor* editor;

    ParamExtender* paramExtender;
    std::vector<EditorParamDrawerBase*> paramDrawers;

    EditorParamDrawerBase* createParamDrawer(int index, const std::string& name, BaseParam* baseParam);

};
