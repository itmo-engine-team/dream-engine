#pragma once

#include "EditorWindow.h"
#include "EditorPopupModalAssetChooser.h"
#include "EditorViewport.h"

class ModelAssetInfo;

class EditorWindowModelViewer : public EditorWindow 
{

public:

    EditorWindowModelViewer(Editor* editor, ModelAssetInfo* modelAssetInfo);

    void Update() override;
    void Render() override;

private:

    EditorViewport* viewport = new EditorViewport(ImVec2(16, 9));

    ModelAssetInfo* modelAssetInfo;

    bool isModelValid;

    std::string modelPath;
    std::string previewTextureAssetName;

    EditorPopupModalAssetChooser* assetChooser;

    void renderModelViewer();
    void renderModelInspector();
    void drawAssetChooser();

    void saveModelAsset();
    void reimportModelAsset();

};

