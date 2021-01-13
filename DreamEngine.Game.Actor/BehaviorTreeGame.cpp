#include "BehaviorTreeGame.h"

#include "BehaviorTreeEditor.h"
#include "BTEditorNodeComposite.h"
#include "BTEditorNodeLogic.h"
#include "BTGameNodeFactory.h"
#include "BTGameNodeComposite.h"
#include "BTGameNodeLogic.h"

BehaviorTreeGame::BehaviorTreeGame(Actor* actor, BehaviorTreeEditor* behaviorTreeEditor) : actor(actor)
{
    if (behaviorTreeEditor != nullptr)
        initBehaviorTreeGame(behaviorTreeEditor);
}

bool BehaviorTreeGame::Update()
{
    return rootNode->Run();
}

BTGameNodeRoot* BehaviorTreeGame::GetRootNode()
{
    return rootNode;
}

Actor* BehaviorTreeGame::GetActor()
{
    return actor;
}

bool BehaviorTreeGame::IsLogging()
{
    return isLogging;
}

void BehaviorTreeGame::initBehaviorTreeGame(BehaviorTreeEditor* behaviorTreeEditor)
{
    rootNode = new BTGameNodeRoot(this);

    std::vector<BTEditorNode*> editorNodeQueue;
    editorNodeQueue.push_back(behaviorTreeEditor->GetRootNode());

    std::vector<BTGameNodeWithChild*> gameNodeQueue;
    gameNodeQueue.push_back(rootNode);

    while (!editorNodeQueue.empty())
    {
        BTEditorNode* currentEditorNode = editorNodeQueue.at(0);
        editorNodeQueue.erase(editorNodeQueue.begin());

        BTGameNodeWithChild* currentGameNode = gameNodeQueue.at(0);
        gameNodeQueue.erase(gameNodeQueue.begin());

        if (currentEditorNode->CanHaveChild())
        {
            for (auto child : currentEditorNode->GetChildrenLinks())
            {
                switch (child.second->GetType())
                {
                    case BTNodeType::Composite:
                    {
                        BTGameNodeComposite* composeNode = BTGameNodeFactory::CreateGameCompositeNodeByType(
                            dynamic_cast<BTEditorNodeComposite*> (child.second)->GetCompositeType(), currentGameNode, this);

                        gameNodeQueue.push_back(composeNode);
                        editorNodeQueue.push_back(child.second);
                        break;
                    }

                    case BTNodeType::Logic:
                    {
                         BTGameNodeFactory::CreateGameLogicNodeByType(dynamic_cast<BTEditorNodeLogic*> (child.second)->GetLogicType(), currentGameNode, this);
                        break;
                    }

                    default:
                        break;
                }
            }
            continue;
        }

        BTGameNodeFactory::CreateGameLogicNodeByType(dynamic_cast<BTEditorNodeLogic*> (currentEditorNode)->GetLogicType(), currentGameNode, this);
    }
}
