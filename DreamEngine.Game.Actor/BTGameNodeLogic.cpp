#include "BTGameNodeLogic.h"

BTGameNodeLogic::BTGameNodeLogic(BTGameNodeRoot* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNode(parentNode, behaviorTree)
{
}

BTGameNodeLogic::BTGameNodeLogic(BTGameNodeComposite* parentNode, BehaviorTreeGame* behaviorTree) : BTGameNode(parentNode, behaviorTree)
{
}
