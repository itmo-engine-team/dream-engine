#include "ModelAssetInfo.h"

ModelAssetInfo::ModelAssetInfo() : AssetInfo(AssetType::Model)
{

}

ModelAssetInfo::ModelAssetInfo(ModelAssetInfo& assetInfo) : AssetInfo(assetInfo)
{

}

void ModelAssetInfo::SetModelPath(std::string& path)
{
    modelPath = path;
}

const std::string& ModelAssetInfo::GetModelPath()
{
    return modelPath;
}

Json ModelAssetInfo::toJson()
{
    Json json = AssetInfo::toJson();

    json["modelPath"] = modelPath;

    return json;
}

void ModelAssetInfo::fromJson(Json json)
{
    AssetInfo::fromJson(json);

    initVariable(json, "modelPath", &modelPath);
}
