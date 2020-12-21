#pragma once

class SceneAssetInfo;
class ACS_Camera;
class ACS_Light;
class InputSystem;
class Graphics;

class BaseSceneViewer
{
public:

    BaseSceneViewer();

    InputSystem* GetInputSystem() const;
    Graphics* GetGraphics() const;

    virtual ACS_Camera* GetCamera() const = 0;
    virtual ACS_Light* GetLight() const = 0;

    virtual void Init(InputSystem* inputSystem, Graphics* graphics);
    virtual void Update(float engineDeltaTime);
    virtual void Render() = 0;
    virtual void RenderShadowMap() = 0;

    void SetDeltaTimeMultiplier(float deltaTimeMultiplier);
    float GetDeltaTimeMultiplier();
    float GetDeltaTime();

protected:

    InputSystem* inputSystem;
    Graphics* graphics;

    float engineDeltaTime;
    float deltaTimeMultiplier = 1;

};

