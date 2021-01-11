#include "ParamAsset.h"
#include "MapUtils.h"

#include "AssetType.h"

ParamAsset::ParamAsset(AssetType assetType)
    : Param<unsigned int>(ParamType::Asset, 0), assetType(assetType)
{

}

ParamAsset::ParamAsset(ParamAsset& paramAsset) : Param<unsigned int>(paramAsset)
{
    this->assetType = paramAsset.assetType;
}

ParamAsset::ParamAsset(Json json) : Param<unsigned int>(ParamType::Asset, 0)
{
    fromJson(json);
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
    json["assetType"] = MapUtils::TryGetByKey<AssetType, std::string>(MAP_ASSET_TYPE_TO_STRING, assetType, "UNKNOWN");

    return json;
}

void ParamAsset::fromJson(Json json)
{
    initVariable(json, "value", &value);

    assetType = AssetType::Model;
}

void ParamAsset::UpdateValue(const BaseParam* paramCopy)
{
    this->Set(dynamic_cast<const ParamAsset*>(paramCopy)->Get());
}
