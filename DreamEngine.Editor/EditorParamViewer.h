#pragma once

#include <vector>
#include "EditorParamDrawer.h"

class Editor;
class ParamExtender;
class ParamAsset;
class ParamInt;
class BaseParam;

class EditorParamViewer
{

public:

    EditorParamViewer(Editor* editor, ParamExtender* paramExtender);
    ~EditorParamViewer();

    BaseParam* Draw();

private:

    Editor* editor;

    ParamExtender* paramExtender;
    std::vector<EditorParamDrawerBase*> paramDrawers;

    EditorParamDrawerBase* createParamDrawer(const std::string& name, BaseParam* baseParam);

};

