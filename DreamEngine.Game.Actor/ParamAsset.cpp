#include "ParamAsset.h"

ParamAsset::ParamAsset(AssetType assetType)
    : Param<unsigned int>(ParamType::Asset, 0), assetType(assetType)
{

}

ParamAsset::ParamAsset(ParamAsset& paramAsset) : Param<unsigned int>(paramAsset)
{
    this->assetType = paramAsset.assetType;
}

AssetType ParamAsset::GetAssetType() const
{
    return assetType;
}

BaseParam* ParamAsset::Copy()
{
    return new ParamAsset(*this);
}
