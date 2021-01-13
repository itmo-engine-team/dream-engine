#pragma once

#include "AssetInfo.h"

class ParamBool;
class ParamVector3;

class ModelAssetInfo : public AssetInfo
{

public:

    ModelAssetInfo();
    ModelAssetInfo(ModelAssetInfo& assetInfo);

    void SetModelPath(std::string& path);
    const std::string& GetModelPath();

    ParamBool* GetUseDefaultBoxParam();
    ParamVector3* GetDefaultBoxVector3Param();

protected:

    Json toJson() override;
    void fromJson(Json json) override;

private:

    ParamBool* useDefaultBoxParam;
    ParamVector3* defautlBoxVector3Param;
    std::string modelPath;

};

class ModelAssetInfoCreator : public AssetInfoCreator
{

    AssetInfo* Create() override
    {
        return new ModelAssetInfo();
    }

    AssetInfo* Duplicate(AssetInfo& assetInfo) override
    {
        return new ModelAssetInfo(dynamic_cast<ModelAssetInfo&>(assetInfo));
    }

};