#pragma once

#include <vector>

#include "Actor.h"
#include "Texture.h"
#include "ModelData.h"

class ACS_Collision;

class GameAssetManager
{

public:

    GameAssetManager(AssetManager* assetManager, Graphics* graphics);
    ~GameAssetManager();

    void Clear();

    // GameObjects
    void AddActor(Actor* actor);
    void DeleteActor(Actor* actor);
    const std::vector<Actor*>& GetActors() const;

    const std::vector<ACS_Collision*>& GetCollisions() const;
    void RegisterCollisions();
    void RegisterActorCollisions(Actor* actor);

    ModelData* GetOrCreateModelData(unsigned int id);
    Texture* GetOrCreateTexture(unsigned int id);

    Actor* FindActorByTag(std::string tag);

    bool IsAnyIntersectionWithLocation(Vector3 targetLocation, Actor* initiator);
    bool IsAnyIntersectionWithCollision(Vector3 targetLocation, Vector2 targetCollisionSize, Actor* initiator);

protected:

    AssetManager* assetManager;
    Graphics* graphics;

    // Game objects
    std::vector<Actor*> actors;
    std::vector<ACS_Collision*> collisions;

    // Graphics objects
    std::map<unsigned int, Texture*> textures;
    std::map<unsigned int, ModelData*> models;

};

