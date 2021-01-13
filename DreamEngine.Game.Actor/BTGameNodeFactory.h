#pragma once

#include "BTNodeType.h"
#include "BTNodeLogicType.h"

class BehaviorTreeGame;
class BTGameNodeWithChild;
class BTGameNodeComposite;
class BTGameNodeLogic;

class BTGameNodeFactory
{

    BTGameNodeFactory() = delete;

public:

    static BTGameNodeComposite* CreateGameCompositeNodeByType(BTNodeCompositeType compositeType, BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree);
    static BTGameNodeLogic* CreateGameLogicNodeByType(BTNodeLogicType logicType, BTGameNodeWithChild* parentNode, BehaviorTreeGame* behaviorTree);
};
