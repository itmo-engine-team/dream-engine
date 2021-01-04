#pragma once

class Graphics;
class AssetManager;
class Game;
class ModelViewer;

class EditorContext
{

public:

    EditorContext(Graphics* graphics,
        AssetManager* assetManager,
        Game* game,
        ModelViewer* modelViewer
    ) : graphics(graphics),
        assetManager(assetManager),
        game(game),
        modelViewer(modelViewer)
    {}

    Graphics* GetGraphics() const;
    AssetManager* GetAssetManager() const;
    Game* GetGame() const;
    ModelViewer* GetModelViewer() const;

private:

    Graphics* graphics;
    AssetManager* assetManager;
    Game* game;
    ModelViewer* modelViewer;

};

