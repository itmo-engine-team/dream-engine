#pragma once

#include "Param.h"

enum class AssetType;

class ParamAsset : public Param<unsigned int>
{

public:

    ParamAsset(AssetType assetType);
    ParamAsset(ParamAsset& paramAsset);

    AssetType GetAssetType() const;

    BaseParam* Copy() override;

private:

    AssetType assetType;

};
