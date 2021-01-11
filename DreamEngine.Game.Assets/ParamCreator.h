#pragma once

#include "Param.h"

class ParamCreator
{

public:

    static BaseParam* CreateFromJson(Json json);

};

