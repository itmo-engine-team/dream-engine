#include "EditorContext.h"

Graphics* EditorContext::GetGraphics() const
{
    return graphics;
}

AssetManager* EditorContext::GetAssetManager() const
{
    return assetManager;
}

Game* EditorContext::GetGame() const
{
    return game;
}

ModelViewer* EditorContext::GetModelViewer() const
{
    return modelViewer;
}
