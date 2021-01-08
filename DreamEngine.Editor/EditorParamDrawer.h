#pragma once
#include <string>

class BaseParam;

class EditorParamDrawerBase
{

public:

    virtual ~EditorParamDrawerBase() = default;
    virtual bool Draw() = 0;
    virtual BaseParam* GetParam() = 0;

};

template<class ParamClass = BaseParam>
class EditorParamDrawer : public EditorParamDrawerBase
{

public:

    EditorParamDrawer(const std::string& name, BaseParam* baseParam) : name(name)
    {
        param = dynamic_cast<ParamClass*>(baseParam);
    }

    BaseParam* GetParam() override
    {
        return param;
    }

protected:

    std::string name;
    ParamClass* param;

};
