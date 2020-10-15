#pragma once

#include <vector>

#include "../GameObject/Actor.h"
#include "../../Graphics/Shader/Shader.h"
#include "../../Graphics/Shader/Texture.h"
#include "../../Graphics/Model/ModelData.h"

class Engine;

class GameAssetManager
{

public:

    GameAssetManager(Engine* engine);
    ~GameAssetManager();

    // GameObjects
    void AddGameObject(GameObject* gameObject);
    std::vector<GameObject*> GetGameObjects() const;

    void AddActor(Actor* actor);
    std::vector<Actor*> GetActors() const;

    // Graphics objects
    void AddShader(Shader* shader);
    void AddTexture(Texture* texture);
    void AddModel(ModelData* modelData);

protected:

    Engine* engine;

    // GameObjects
    std::vector<GameObject*> gameObjects;
    std::vector<Actor*> actors;

    // Graphics objects
    std::vector<Shader*> shaders;
    std::vector<Texture*> textures;
    std::vector<ModelData*> models;

};

