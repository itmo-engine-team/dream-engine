#pragma once

#include "Param.h"

#include "AssetType.h"

class ParamAsset : public Param<unsigned int>
{



private:

    AssetType type;

};
