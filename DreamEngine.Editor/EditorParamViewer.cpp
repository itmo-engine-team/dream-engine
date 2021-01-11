#include "EditorParamViewer.h"

#include "Param.h"
#include "EditorParamDrawerInt.h"
#include "EditorParamDrawerFloat.h"
#include "EditorParamDrawerString.h"
#include "EditorParamDrawerAsset.h"
#include "EditorParamDrawerTransform.h"
#include "ParamExtender.h"

EditorParamViewer::EditorParamViewer(Editor* editor, ParamExtender* paramExtender, int index)
    : editor(editor), paramExtender(paramExtender)
{
    for (auto iter : paramExtender->GetParamMap())
    {
        paramDrawers.push_back(createParamDrawer(index, iter.first, iter.second));
        index++;
    }
}

EditorParamViewer::~EditorParamViewer()
{
    for (auto paramDrawer : paramDrawers)
    {
        delete paramDrawer;
    }
}

BaseParam* EditorParamViewer::Draw()
{
    BaseParam* changedParam = nullptr;
    for (auto drawer : paramDrawers)
    {
        if (drawer->Draw())
        {
            changedParam = drawer->GetParam();
        }
    }
    return changedParam;
}

EditorParamDrawerBase* EditorParamViewer::createParamDrawer(int index, 
    const std::string& name, BaseParam* baseParam)
{
    switch (baseParam->GetType())
    {
        case ParamType::Int:
            return new EditorParamDrawerInt(index, name, baseParam);
        case ParamType::Asset:
            return new EditorParamDrawerAsset(editor, index, name, baseParam);
        case ParamType::Transform:
            return new EditorParamDrawerTransform(index, name, baseParam);
        case ParamType::Float:
            return new EditorParamDrawerFloat(index, name, baseParam);
        case ParamType::String:
            return new EditorParamDrawerString(index, name, baseParam);
        default:
            break;
    }
}
