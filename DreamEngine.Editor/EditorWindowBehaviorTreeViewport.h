#pragma once
#include "EditorWindow.h"

class BTAssetInfo;

class EditorWindowBehaviorTreeViewport : public EditorWindow
{

public:

    EditorWindowBehaviorTreeViewport(Editor* editor, BTAssetInfo* assetInfo);

    void Init() override;
    void Update() override;
    void Render() override;

private:

    BTAssetInfo* assetInfo;

};

