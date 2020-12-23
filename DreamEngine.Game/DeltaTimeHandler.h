#pragma once

class DeltaTimeHandler
{

public:

    DeltaTimeHandler() = default;

    float GetDeltaTime() const;
    void SetParentDeltaTime(float deltaTime);

    float GetMultiplier() const;
    void SetMultiplier(float multiplier);

private:

    float deltaTime = 0;
    float multiplier = 1;

};

