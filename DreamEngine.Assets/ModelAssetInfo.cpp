#include "ModelAssetInfo.h"

#include "ParamBool.h"
#include "ParamVector3.h"

ModelAssetInfo::ModelAssetInfo() : AssetInfo(AssetType::Model)
{
    useDefaultBoxParam = new ParamBool();
    defautlBoxVector3Param = new ParamVector3();
}

ModelAssetInfo::ModelAssetInfo(ModelAssetInfo& assetInfo) : AssetInfo(assetInfo)
{
    useDefaultBoxParam->Update(assetInfo.useDefaultBoxParam);
    defautlBoxVector3Param->Update(assetInfo.defautlBoxVector3Param);
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

ParamVector3* ModelAssetInfo::GetDefaultBoxVector3Param()
{
    return defautlBoxVector3Param;
}

Json ModelAssetInfo::toJson()
{
    Json json = AssetInfo::toJson();

    json["useDefaultBox"] = useDefaultBoxParam->toJson();
    json["defautlBoxVector3"] = defautlBoxVector3Param->toJson();
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

    if (json.contains("defautlBoxVector3"))
    {
        defautlBoxVector3Param->fromJson(json["defautlBoxVector3"]);
    }

    initVariable(json, "modelPath", &modelPath);
}
