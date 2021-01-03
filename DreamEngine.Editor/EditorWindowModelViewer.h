#pragma once

#include "EditorWindow.h"
#include "EditorPopupModalAssetChooser.h"

class ModelAssetInfo;

class EditorWindowModelViewer : public EditorWindow 
{

public: 

    EditorWindowModelViewer(Editor* editor, ModelAssetInfo* modelAssetInfo);

    void Update() override;
    void Render() override;

private:

    ModelAssetInfo* modelAssetInfo;

    std::string modelPath;
    std::string previewTextureAssetName;

    EditorPopupModalAssetChooser* assetChooser;

    void renderModelViewer();
    void renderModelInspector();
    void drawAssetChooser();

    void saveModelAsset();
    void reimportModelAsset();

};

