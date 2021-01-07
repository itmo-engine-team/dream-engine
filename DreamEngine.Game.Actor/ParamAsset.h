#pragma once

#include "Param.h"

enum class AssetType;

class ParamAsset : public Param<unsigned int>
{

public:

    ParamAsset(AssetType assetType);

    void Set(unsigned int value) override;
    void SetDef() override;

    bool IsValid() const;

private:

    bool isValid = false;
    AssetType assetType;

};
