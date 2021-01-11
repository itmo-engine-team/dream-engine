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
    Json json = Param::toJson();

    json["value"] = value;
    json["assetType"] = MapUtils::TryGetByKey<AssetType, std::string>(MAP_ASSET_TYPE_TO_STRING, assetType, "UNKNOWN");

    return json;
}

void ParamAsset::fromJson(Json json)
{
    Param::fromJson(json);

    initVariable(json, "value", &value);

    std::string stringType;
    initVariable(json, "assetType", &stringType);
    assetType = MapUtils::TryGetByValue<AssetType, std::string>(MAP_ASSET_TYPE_TO_STRING, stringType, AssetType::Unknown);
}

void ParamAsset::UpdateValue(const BaseParam* paramCopy)
{
    if (paramCopy->IsDefault())
        SetDef();
    else
        Set(dynamic_cast<const ParamAsset*>(paramCopy)->Get());
}
