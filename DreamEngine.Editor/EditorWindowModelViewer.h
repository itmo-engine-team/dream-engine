#pragma once
#include "Texture.h"
#include "EditorWindow.h"
#include "EditorPopupModelAssetChooser.h"

class EditorWindowModelViewer : public EditorWindow 
{

public: 

    EditorWindowModelViewer(Editor* editor, Texture* assetIcon);

    void Update() override;
    void Render() override;

    bool IsOpened();

private:

    bool isOpened = true;
    std::string currentAssetInfoName;

    EditorPopupModelAssetChooser* assetChooser;
    AssetType assetType;
    Texture* currentTexture;

    void renderModelViewer();
    void renderModelInspector();
    void drawAssetChooser();

};

