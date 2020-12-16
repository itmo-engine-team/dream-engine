#include "GameAssetManager.h"

GameAssetManager::GameAssetManager()
{

}

GameAssetManager::~GameAssetManager()
{
    // TODO 
}

void GameAssetManager::AddGameObject(GameObject* gameObject)
{
    gameObjects.push_back(gameObject);
}

std::vector<GameObject*> GameAssetManager::GetGameObjects() const
{
    return gameObjects;
}

void GameAssetManager::AddActor(Actor* actor)
{
    actors.push_back(actor);
    AddGameObject(actor);
}

std::vector<Actor*> GameAssetManager::GetActors() const
{
    return actors;
}

std::vector<ModelData*> GameAssetManager::GetModelData() const
{
    return models;
}

void GameAssetManager::AddTexture(Texture* texture)
{
    textures.push_back(texture);
}

void GameAssetManager::AddModel(ModelData* modelData)
{
    models.push_back(modelData);
}
