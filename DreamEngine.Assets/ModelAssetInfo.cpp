#include "ModelAssetInfo.h"

#include "ParamBool.h"
#include "ParamVector3.h"

ModelAssetInfo::ModelAssetInfo() : AssetInfo(AssetType::Model)
{
    useDefaultBoxParam = new ParamBool();
    defaultBoxColorParam = new ParamVector3();
}

ModelAssetInfo::ModelAssetInfo(ModelAssetInfo& assetInfo) : AssetInfo(assetInfo)
{
    useDefaultBoxParam->Update(assetInfo.useDefaultBoxParam);
    defaultBoxColorParam->Update(assetInfo.defaultBoxColorParam);
    modelPath = assetInfo.modelPath;
}

void ModelAssetInfo::SetModelPath(std::string& path)
{
    modelPath = path;
}

const std::string& ModelAssetInfo::GetModelPath()
{
    return modelPath;
}

ParamBool* ModelAssetInfo::GetUseDefaultBoxParam()
{
    return useDefaultBoxParam;
}

ParamVector3* ModelAssetInfo::GetDefaultBoxColorParam()
{
    return defaultBoxColorParam;
}

Json ModelAssetInfo::toJson()
{
    Json json = AssetInfo::toJson();

    json["useDefaultBox"] = useDefaultBoxParam->toJson();
    json["defaultBoxColor"] = defaultBoxColorParam->toJson();
    json["modelPath"] = modelPath;

    return json;
}

void ModelAssetInfo::fromJson(Json json)
{
    AssetInfo::fromJson(json);

    if (json.contains("useDefaultBox"))
    {
        useDefaultBoxParam->fromJson(json["useDefaultBox"]);
    }

    if (json.contains("defaultBoxColor"))
    {
        defaultBoxColorParam->fromJson(json["defaultBoxColor"]);
    }

    initVariable(json, "modelPath", &modelPath);
}
