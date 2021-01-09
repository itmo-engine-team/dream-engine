#include "BTGameNodeFactory.h"

#include "BTGameNodeSelector.h"
#include "BTGameNodeSequence.h"
#include "BTGMoveTo.h"

BTGameNodeComposite* BTGameNodeFactory::CreateGameCompositeNodeByType(BTNodeCompositeType compositeType, 
    BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree)
{
    switch (compositeType)
    {
        case BTNodeCompositeType::Selector:
            return new BTGameNodeSelector(parentNode, behaviorTree);

        case BTNodeCompositeType::Sequencer:
            return new BTGameNodeSequence(parentNode, behaviorTree);

        default:
            return nullptr;
    }
}

BTGameNodeLogic* BTGameNodeFactory::CreateGameLogicNodeByType(BTNodeLogicType logicType,
    BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree)
{
    switch (logicType)
    {
        case BTNodeLogicType::MoveTo:
            return new BTGMoveTo(parentNode, behaviorTree);

        default:
            return nullptr;
    }
}
