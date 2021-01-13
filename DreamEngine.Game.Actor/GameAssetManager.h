#pragma once

#include <vector>

#include "Actor.h"
#include "Texture.h"
#include "ModelData.h"

class ActorAssetInfo;
class ACS_Collision;

class GameAssetManager
{

public:

    GameAssetManager(AssetManager* assetManager, Graphics* graphics);
    ~GameAssetManager();

    bool IsGameOver() const;
    bool IsWin() const;
    void GameOver(bool isWin);

    void Clear();

    // GameObjects
    void CreateActorByAsset(ActorContext* context, unsigned int id, Vector3 position);
    void AddActor(Actor* actor);
    void RequestToDeleteActor(Actor* actor);
    void DeleteActor(Actor* actor);
    void HandleNewActors();
    const std::vector<Actor*>& GetActors() const;
    const std::vector<Actor*>& GetActorsToDelete() const;
    const std::vector<Actor*>& GetActorsToAdd() const;

    const std::vector<ACS_Collision*>& GetCollisions() const;
    void RegisterCollisions();
    void RegisterActorCollisions(Actor* actor);

    ModelData* GetOrCreateModelData(unsigned int id);
    Texture* GetOrCreateTexture(unsigned int id);

    Actor* FindActorByTag(std::string tag);
    std::vector<Actor*> FindAllActorsByTag(std::string tag);

    bool IsAnyIntersectionWithLocation(Vector3 targetLocation, Actor* initiator, bool ignoreTrigger);
    bool IsAnyIntersectionWithCollision(Vector3 targetLocation, 
        Vector2 targetCollisionSize, Actor* initiator, bool ignoreTrigger);
    bool CheckActorsCollision(Actor* initiator, Actor* target, bool ignoreTrigger);

    int GetScore();
    void AddScore(int deltaScore);

protected:

    bool isGameOver = false;
    bool isWin;

    AssetManager* assetManager;
    Graphics* graphics;

    // Game objects
    std::vector<Actor*> actors;
    std::vector<Actor*> actorsToDelete;
    std::vector<Actor*> actorsToAdd;
    std::vector<ACS_Collision*> collisions;

    // Graphics objects
    std::map<unsigned int, Texture*> textures;
    std::map<unsigned int, ModelData*> models;

    int score = 0;

};

