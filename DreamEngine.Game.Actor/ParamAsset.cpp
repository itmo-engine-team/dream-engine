#include "ParamAsset.h"

ParamAsset::ParamAsset(AssetType assetType)
    : Param<unsigned int>(ParamType::Asset, 0), assetType(assetType)
{

}

void ParamAsset::Set(unsigned int value)
{
    Param::Set(value);
    isValid = true;
}

void ParamAsset::SetDef()
{
    Param::SetDef();
    isValid = false;
}

bool ParamAsset::IsValid() const
{
    return isValid;
}
