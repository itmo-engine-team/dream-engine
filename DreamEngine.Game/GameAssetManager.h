#pragma once

#include <vector>

#include "Actor.h"
#include "Texture.h"
#include "ModelData.h"

class GameAssetManager
{

public:

    GameAssetManager();
    ~GameAssetManager();

    // GameObjects
    void AddGameObject(GameObject* gameObject);
    std::vector<GameObject*> GetGameObjects() const;

    void AddActor(Actor* actor);
    std::vector<Actor*> GetActors() const;

    std::vector<ModelData*> GetModelData() const;

    // Graphics objects
    void AddTexture(Texture* texture);
    void AddModel(ModelData* modelData);

protected:

    // GameObjects
    std::vector<GameObject*> gameObjects;
    std::vector<Actor*> actors;

    // Graphics objects
    std::vector<Texture*> textures;
    std::vector<ModelData*> models;

};

