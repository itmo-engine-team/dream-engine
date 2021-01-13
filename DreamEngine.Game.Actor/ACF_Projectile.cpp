#include "ACF_Projectile.h"
#include "Transform.h"
#include "ParamVector3.h"
#include "ParamFloat.h"
#include "DeltaTimeHandler.h"

ACF_Projectile::ACF_Projectile(Actor* actor)
    : ActorComponentFixed(actor)
{
    directionParam = new ParamVector3();
    AddParam("Direction", directionParam);

    speedParam = new ParamFloat();
    AddParam("Speed", speedParam);
}

void ACF_Projectile::onUpdate()
{
    actor->GetTransform()->AddWorldPosition(actor->GetContext()->GetDeltaTimeHandler()->GetDeltaTime()
        * directionParam->Get() * speedParam->Get());
}
