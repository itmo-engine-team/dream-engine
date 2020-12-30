#pragma once
#include "Texture.h"
#include "EditorWindow.h"
#include "EditorPopupModelAssetChooser.h"

class EditorWindowModelViewer : public EditorWindow 
{

public: 

    EditorWindowModelViewer(Editor* editor, AssetType currentAssetType, Texture* assetIcon);

    void Update() override;
    void Render() override;

    bool GetResult();

private:

    bool result = false;
    std::string currentAssetInfoName;

    EditorPopupModelAssetChooser* assetChooser;
    AssetType assetType;
    Texture* currentTexture;

    void renderModelViewer();
    void renderModelInspector();
    void drawAssetChooser();

};

