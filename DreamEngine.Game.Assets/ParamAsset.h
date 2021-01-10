#pragma once

#include "Param.h"

enum class AssetType;

class ParamAsset : public Param<unsigned int>
{

public:

    static ParamAsset* CreateFromJson(Json json);

    ParamAsset(AssetType assetType);
    ParamAsset(ParamAsset& paramAsset);

    AssetType GetAssetType() const;

    BaseParam* Copy() override;

    Json toJson() override;
    void fromJson(Json json) override;

protected:

    void UpdateValue(const BaseParam* paramCopy) override;

private:

    AssetType assetType;

};
