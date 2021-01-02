#pragma once

#include "EditorWindow.h"
#include "Texture.h"

class TextureAssetInfo;

class EditorWindowTextureViewer : public EditorWindow
{

public:

    EditorWindowTextureViewer(Editor* editor, TextureAssetInfo* textureAssetInfo);

    void Update() override;
    void Render() override;

private:

    TextureAssetInfo* textureAssetInfo;
    Texture* textureInstance;

    std::string texturePath;

    void renderTextureViewer();
    void renderTextureInspector();

    void saveTextureAsset();
    void reimportTextureAsset();

};

