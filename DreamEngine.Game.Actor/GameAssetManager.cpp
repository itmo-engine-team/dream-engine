#include "GameAssetManager.h"

#include "ModelAssetInfo.h"
#include "TextureAssetInfo.h"
#include "ACF_Tag.h"
#include "ACS_Collision.h"
#include "ParamBool.h"
#include "MeshRenderer.h"
#include "ParamVector3.h"

GameAssetManager::GameAssetManager(AssetManager* assetManager, Graphics* graphics)
    : assetManager(assetManager), graphics(graphics)
{

}

GameAssetManager::~GameAssetManager()
{
    Clear();
}

bool GameAssetManager::IsGameOver() const
{
    return isGameOver;
}

void GameAssetManager::GameOver()
{
    isGameOver = true;
}

void GameAssetManager::Clear()
{
    isGameOver = false;

    for (auto actor : actors)
    {
        delete actor;
    }
    actors.clear();
    collisions.clear();

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
    RegisterActorCollisions(actor);
}

void GameAssetManager::RequestToDeleteActor(Actor* actor)
{
    actorsToDelete.push_back(actor);
}

void GameAssetManager::DeleteActor(Actor* actor)
{
    for (auto actorIter = actors.begin(); actorIter < actors.end(); ++actorIter)
    {
        if (*actorIter == actor)
        {
            // Remove actor collisions
            auto actorCollisions = actor->FindComponents<ACS_Collision>();
            for (auto collision : actorCollisions)
            {
                for (auto collisionIter = collisions.begin();
                    collisionIter < collisions.end(); ++collisionIter)
                {
                    if (*collisionIter == collision)
                    {
                        collisions.erase(collisionIter);
                        break;
                    }
                }
            }

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

const std::vector<Actor*>& GameAssetManager::GetActorsToDelete() const
{
    return actorsToDelete;
}

const std::vector<ACS_Collision*>& GameAssetManager::GetCollisions() const
{
    return collisions;
}

void GameAssetManager::RegisterCollisions()
{
    for (auto actor : actors)
    {
        RegisterActorCollisions(actor);
    }
}

void GameAssetManager::RegisterActorCollisions(Actor* actor)
{
    auto actorCollisions = actor->FindComponents<ACS_Collision>();
    for (auto collision : actorCollisions)
    {
        collisions.push_back(collision);
    }
}

ModelData* GameAssetManager::GetOrCreateModelData(unsigned int id)
{
    auto modelIter = models.find(id);
    if (modelIter == models.end())
    {
        // Model is not exist, than create it
        auto modelAssetInfo = dynamic_cast<ModelAssetInfo*>(
            assetManager->GetAssetByType(AssetType::Model, id));

        ModelData* modelData = nullptr;
        if (modelAssetInfo->GetUseDefaultBoxParam()->Get())
        {
            auto boxColor = modelAssetInfo->GetDefaultBoxColorParam()->Get();
            modelData = graphics->GetMeshRenderer()->CreateBoxModel(
                { boxColor.x, boxColor.y, boxColor.z, 1.0f }, { 1.0f, 1.0f, 1.0f });
        }
        else
        {
            modelData = new ModelData(graphics->GetMeshRenderer(), modelAssetInfo->GetModelPath());
        }

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
    return nullptr;
}

std::vector<Actor*> GameAssetManager::FindAllActorsByTag(std::string tag)
{
    std::vector<Actor*> actorsWithTag;
    for (Actor* actor : actors)
    {
        ACF_Tag* tagComponent = actor->FindComponent<ACF_Tag>();
        if (tagComponent == nullptr) continue;

        if (tag == tagComponent->GetTag()) 
            actorsWithTag.push_back(actor);
    }
    return actorsWithTag;
}

bool GameAssetManager::IsAnyIntersectionWithLocation(Vector3 targetLocation, Actor* initiator, bool ignoreTrigger)
{
    for (auto collision : collisions)
    {
        if (collision->GetActor() == initiator 
                || (ignoreTrigger && collision->IsTrigger()) || !collision->IsActive()) continue;

        if (collision->IsPointIntersects(targetLocation)) return true;
    }
    return false;
}

bool GameAssetManager::IsAnyIntersectionWithCollision(Vector3 targetLocation, Vector2 targetCollisionSize,
    Actor* initiator, bool ignoreTrigger)
{
    for(auto collision : collisions)
    {
        if (collision->GetActor() == initiator 
            || (ignoreTrigger && collision->IsTrigger()) || !collision->IsActive()) continue;

        if (collision->IsCollisionIntersects(targetLocation, targetCollisionSize)) return true;
    }
    return false;
}

bool GameAssetManager::CheckActorsCollision(Actor* initiator, Actor* target, bool ignoreTrigger)
{
    std::vector<ACS_Collision*> initiatorCollisions = initiator->FindComponents<ACS_Collision>();
    std::vector<ACS_Collision*> targetCollisions = target->FindComponents<ACS_Collision>();

    if (initiatorCollisions.empty() || targetCollisions.empty()) return false;

    for (ACS_Collision* initiatorCollision : initiatorCollisions)
    {
        if (initiatorCollision->IsTrigger() == true && ignoreTrigger == true) continue;

        for (ACS_Collision* targetCollision : targetCollisions)
        {
            if (targetCollision->IsTrigger() == true && ignoreTrigger == true) continue;

            if (initiatorCollision->IsCollisionIntersects(targetCollision->GetTransform()->GetWorldPosition(), targetCollision->GetSize()))
                return true;
        }
    }

    return false;
}

int GameAssetManager::GetScore()
{
    return score;
}

void GameAssetManager::AddScore(int deltaScore)
{
    score += deltaScore;
}
