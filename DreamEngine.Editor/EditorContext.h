#pragma once
#include "ActorViewer.h"

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
        ModelViewer* modelViewer,
        ActorViewer* actorViewer
    ) : graphics(graphics),
        assetManager(assetManager),
        game(game),
        modelViewer(modelViewer),
        actorViewer(actorViewer)
    {}

    Graphics* GetGraphics() const;
    AssetManager* GetAssetManager() const;
    Game* GetGame() const;
    ModelViewer* GetModelViewer() const;
    ActorViewer* GetActorViewer() const;

private:

    Graphics* graphics;
    AssetManager* assetManager;
    Game* game;
    ModelViewer* modelViewer;
    ActorViewer* actorViewer;

};

