#pragma once

#include "AssetInfo.h"
#include "BehaviorTreeEditor.h"

class BTAssetInfo : public AssetInfo
{

public:

    BTAssetInfo();
    BTAssetInfo(BTAssetInfo& assetInfo);
    ~BTAssetInfo();

    BehaviorTreeEditor* GetBTEditor();

protected:

    Json toJson() override;
    void fromJson(Json json) override;

private:

    BehaviorTreeEditor* behaviorTree;

};

class BTAssetInfoCreator : public AssetInfoCreator
{

    AssetInfo* Create() override
    {
        return new BTAssetInfo();
    }

    AssetInfo* Duplicate(AssetInfo& assetInfo) override
    {
        return new BTAssetInfo(dynamic_cast<BTAssetInfo&>(assetInfo));
    }

};

