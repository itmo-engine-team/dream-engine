#pragma once

#include "AssetInfo.h"

class AssetInfoFactory
{

    template<class AssetInfoClass = AssetInfo>
    static AssetInfoClass* CreateAssetInfo()
    {
        // TODO Remove constructor argument when real assets will be created
        return new AssetInfoClass(AssetType::Actor);
    }

};

