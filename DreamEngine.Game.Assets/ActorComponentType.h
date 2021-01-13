#pragma once

enum class ACS_Type
{
    Collision,
    StaticModel,

    UNKNOWN
};

const std::map<ACS_Type, std::string> MAP_ACS_TYPE_TO_STRING = {
    { ACS_Type::Collision, "Collision" },
    { ACS_Type::StaticModel, "Static Model" },
};

enum class ACF_Type
{
    AI,
    Tag,
    TargetTag,
    Movement,
    PlayerMovement,
    GameOverOnTargetCollision,
    DestroyTargetOnCollision,
    CollectScoreOnCollision,
    Projectile,

    UNKNOWN
};

const std::map<ACF_Type, std::string> MAP_ACF_TYPE_TO_STRING = {
    { ACF_Type::AI, "AI" },
    { ACF_Type::Tag, "Tag" },
    { ACF_Type::TargetTag, "Target Tag" },
    { ACF_Type::Movement, "Movement" },
    { ACF_Type::PlayerMovement, "PlayerMovement" },
    { ACF_Type::GameOverOnTargetCollision, "GameOver On Target Collision" },
    { ACF_Type::DestroyTargetOnCollision, "Destroy Target On Collision" },
    { ACF_Type::CollectScoreOnCollision, "Collect Score On Collision" },
    { ACF_Type::Projectile, "Projectile" },
};