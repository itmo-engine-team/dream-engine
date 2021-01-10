#include "ParamAsset.h"
#include "MapUtils.h"

ParamAsset* ParamAsset::CreateFromJson(Json json)
{
    
}

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

Json ParamAsset::toJson()
{
    Json json = {};

    json["value"] = value;
    json["assetType"] = MapUtils::TryGetByKey<AssetType, std::string>()

    return json;
}

void ParamAsset::fromJson(Json json)
{
    initVariable(json, "value", &value);
}

void ParamAsset::UpdateValue(const BaseParam* paramCopy)
{
    this->Set(dynamic_cast<const ParamAsset*>(paramCopy)->Get());
}
