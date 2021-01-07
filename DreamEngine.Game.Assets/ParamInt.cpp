#include "ParamInt.h"

ParamInt::ParamInt(int def) : Param<int>(ParamType::Int, def)
{

}

ParamInt::ParamInt(ParamInt& param) : Param<int>(param)
{
    
}

BaseParam* ParamInt::Copy()
{
    return new ParamInt(*this);
}
