#include "EditorParamViewer.h"

#include "Param.h"
#include "EditorParamDrawerInt.h"
#include "EditorParamDrawerAsset.h"
#include "ParamExtender.h"

EditorParamViewer::EditorParamViewer(Editor* editor, ParamExtender* paramExtender)
    : editor(editor), paramExtender(paramExtender)
{
    for (auto iter : paramExtender->GetParamMap())
    {
        paramDrawers.push_back(createParamDrawer(iter.first, iter.second));
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

EditorParamDrawerBase* EditorParamViewer::createParamDrawer(const std::string& name, BaseParam* baseParam)
{
    switch (baseParam->GetType())
    {
        case ParamType::Int:
            return new EditorParamDrawerInt(name, baseParam);
        case ParamType::Asset:
            return new EditorParamDrawerAsset(editor, name, baseParam);
        default:
            break;
    }
}
