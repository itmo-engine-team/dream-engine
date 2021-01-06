#pragma once

template<typename Type>
class Param
{

public:

    Param(Type def)
    {
        param = def;
    }

    void Set(Type param)
    {
        this->param;
    }

    Type Get() const
    {
        return param;
    }

protected:

    Type param;

};

