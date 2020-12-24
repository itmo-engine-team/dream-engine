#pragma once

class Graphics;
class AssetManager;
class Game;

class EditorContext
{

public:

    EditorContext(Graphics* graphics,
        AssetManager* assetManager,
        Game* game
    ) : graphics(graphics),
        assetManager(assetManager),
        game(game)
    {}

    Graphics* GetGraphics() const;
    AssetManager* GetAssetManager() const;
    Game* GetGame() const;

private:

    Graphics* graphics;
    AssetManager* assetManager;
    Game* game;

};

