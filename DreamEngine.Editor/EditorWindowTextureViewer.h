#pragma once

#include "EditorWindow.h"
#include "Texture.h"
#include "EditorViewport.h"

class TextureAssetInfo;

class EditorWindowTextureViewer : public EditorWindow
{

public:

    EditorWindowTextureViewer(Editor* editor, TextureAssetInfo* textureAssetInfo);

    void Update() override;
    void Render() override;

private:

    EditorViewport* viewport = new EditorViewport(ImVec2(10, 10));

    TextureAssetInfo* textureAssetInfo;
    Texture* textureInstance;

    std::string texturePath;

    void renderTextureViewer();
    void renderTextureInspector();

    void saveTextureAsset();
    void reimportTextureAsset();

};

