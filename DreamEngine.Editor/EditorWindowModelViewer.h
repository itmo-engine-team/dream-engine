#pragma once

#include "EditorWindow.h"
#include "EditorPopupModalAssetChooser.h"
#include "EditorViewport.h"
#include "TextureAssetInfo.h"
#include "EditorParamDrawerBool.h"
#include "EditorParamDrawerVector3.h"

class ModelAssetInfo;

class EditorWindowModelViewer : public EditorWindow 
{

public:

    EditorWindowModelViewer(Editor* editor, ModelAssetInfo* modelAssetInfo);

    void Init() override;
    void Update() override;
    void Render() override;

private:

    EditorViewport* viewport = new EditorViewport(ImVec2(16, 9));

    ModelAssetInfo* modelAssetInfo;

    bool isModelValid;

    std::string modelPath;
    TextureAssetInfo* previewTextureAsset = nullptr;

    EditorPopupModalAssetChooser* assetChooser = nullptr;

    ParamBool* paramBool = nullptr;
    ParamVector3* paramVector3 = nullptr;
    EditorParamDrawerBool* paramDrawerBool = nullptr;
    EditorParamDrawerVector3* paramDrawVector3 = nullptr;

    void renderModelViewer();
    void renderModelInspector();
    void drawAssetChooser();

    void saveModelAsset();
    void reimportModelAsset();

};

