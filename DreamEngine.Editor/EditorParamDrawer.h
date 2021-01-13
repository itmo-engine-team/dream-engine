#pragma once
#include <string>

class BaseParam;

class EditorParamDrawerBase
{

public:

    virtual ~EditorParamDrawerBase() = default;
    virtual bool Draw() = 0;
    virtual BaseParam* GetParam() = 0;
    virtual int GetRequiredIndexCount()
    {
        return 1;
    }

};

template<class ParamClass = BaseParam>
class EditorParamDrawer : public EditorParamDrawerBase
{

public:

    EditorParamDrawer(int index, const std::string& name, BaseParam* baseParam) : index(index), name(name)
    {
        param = dynamic_cast<ParamClass*>(baseParam);
    }

    BaseParam* GetParam() override
    {
        return param;
    }

protected:

    int index;
    std::string name;
    ParamClass* param;

};

