#pragma once

#include <Serializable.h>
#include "ParamExtender.h"

class ActorComponent;

class ActorComponentInfo : public Serializable
{

public:

    ActorComponentInfo() = default;
    ActorComponentInfo(ActorComponentInfo& componentInfo);
    virtual ~ActorComponentInfo() = 0;

    const std::string& GetName() const;
    void SetName(const std::string& name);

    ActorComponent* GetComponentRef() const;
    void SetComponentRef(ActorComponent* componentRef);

    ParamExtender* GetParamExtender() const;

protected:

    Json toJson() override;
    void fromJson(Json json) override;

private:

    std::string name;
    ActorComponent* componentRef = nullptr;

    ParamExtender* paramExtender = new ParamExtender();

};

