#pragma once

#include <Serializable.h>

class ActorComponentInfo : public Serializable
{

public:

    ActorComponentInfo() = default;
    virtual ~ActorComponentInfo() = 0;

    const std::string& GetName() const;
    void SetName(const std::string& name);

protected:

    Json toJson() override;
    void fromJson(Json json) override;

private:

    std::string name;

};

