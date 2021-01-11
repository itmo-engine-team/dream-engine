#pragma once

#include "Param.h"

enum class AssetType;

class ParamAsset : public Param<unsigned int>
{

public:

    ParamAsset(AssetType assetType);
    ParamAsset(ParamAsset& paramAsset);
    ParamAsset(Json json);

    AssetType GetAssetType() const;

    BaseParam* Copy() override;

    Json toJson() override;
    void fromJson(Json json) override;

protected:

    void UpdateValue(const BaseParam* paramCopy) override;

private:

    AssetType assetType;

};
