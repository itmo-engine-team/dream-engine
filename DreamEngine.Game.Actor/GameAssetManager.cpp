#include "GameAssetManager.h"

#include "ModelAssetInfo.h"
#include "TextureAssetInfo.h"
#include "ACF_Tag.h"

GameAssetManager::GameAssetManager(AssetManager* assetManager, Graphics* graphics)
    : assetManager(assetManager), graphics(graphics)
{

}

GameAssetManager::~GameAssetManager()
{
    Clear();
}

void GameAssetManager::Clear()
{
    for (auto actor : actors)
    {
        delete actor;
    }
    actors.clear();

    for (auto iter : models)
    {
        delete iter.second;
    }
    models.clear();

    for (auto iter : textures)
    {
        delete iter.second;
    }
    textures.clear();
}

void GameAssetManager::AddActor(Actor* actor)
{
    actors.push_back(actor);
}

void GameAssetManager::DeleteActor(Actor* actor)
{
    for (auto actorIter = actors.begin(); actorIter < actors.end(); ++actorIter)
    {
        if (*actorIter == actor)
        {
            delete* actorIter;
            actors.erase(actorIter);
            return;
        }
    }
}

const std::vector<Actor*>& GameAssetManager::GetActors() const
{
    return actors;
}

ModelData* GameAssetManager::GetOrCreateModelData(unsigned int id)
{
    auto modelIter = models.find(id);
    if (modelIter == models.end())
    {
        // Model is not exist, than create it
        auto modelAssetInfo = dynamic_cast<ModelAssetInfo*>(
            assetManager->GetAssetByType(AssetType::Model, id));

        auto modelData = new ModelData(graphics->GetMeshRenderer(), modelAssetInfo->GetModelPath());
        models[id] = modelData;
        return modelData;
    }

    return modelIter->second;
}

Texture* GameAssetManager::GetOrCreateTexture(unsigned int id)
{
    auto textureIter = textures.find(id);
    if (textureIter == textures.end())
    {
        // Model is not exist, than create it
        auto textureAssetInfo = dynamic_cast<TextureAssetInfo*>(
            assetManager->GetAssetByType(AssetType::Texture, id));

        std::wstring wstringTexturePath = std::wstring(textureAssetInfo->GetTexturePath().begin(),
            textureAssetInfo->GetTexturePath().end());
        auto texture = new Texture(graphics, wstringTexturePath.data());
        textures[id] = texture;
        return texture;
    }

    return textureIter->second;
}

Actor* GameAssetManager::FindActorByTag(std::string tag)
{
    for (Actor* actor : actors)
    {
        ACF_Tag* tagComponent = actor->FindComponent<ACF_Tag>();
        if (tagComponent == nullptr) continue;

        if (tag == tagComponent->GetTag()) return actor;
    }
}
