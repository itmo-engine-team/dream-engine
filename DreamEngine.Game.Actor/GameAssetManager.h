#pragma once

#include <vector>

#include "Actor.h"
#include "Texture.h"
#include "ModelData.h"

class GameAssetManager
{

public:

    GameAssetManager(AssetManager* assetManager, Graphics* graphics);
    ~GameAssetManager();

    void Clear();

    // GameObjects
    void AddActor(Actor* actor);
    std::vector<Actor*> GetActors() const;

    ModelData* GetOrCreateModelData(unsigned int id);
    Texture* GetOrCreateTexture(unsigned int id);

protected:

    AssetManager* assetManager;
    Graphics* graphics;

    // Game objects
    std::vector<Actor*> actors;

    // Graphics objects
    std::map<unsigned int, Texture*> textures;
    std::map<unsigned int, ModelData*> models;

};

