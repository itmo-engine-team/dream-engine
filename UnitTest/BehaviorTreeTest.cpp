#include "pch.h"

#include <iostream>

#include "Actor.h"
#include "BehaviorTreeGame.h"
#include "BehaviorTreeEditor.h"
#include "BTEditorNodeComposite.h"
#include "BTEditorNodeLogic.h"

TEST(BehaviorTreeTest, BTInitTest)
{
    BehaviorTreeEditor* treeEditor = new BehaviorTreeEditor();

    auto selector1 = static_cast<BTEditorNodeComposite*>(treeEditor->CreateNode(BTNodeType::Composite));
    selector1->SetCompositeType(BTNodeCompositeType::Selector);
    treeEditor->CreateLink(treeEditor->GetRootNode()->GetChildrenAttributeId(), selector1->GetParentAttributeId());

    auto sequencer1 = static_cast<BTEditorNodeComposite*>(treeEditor->CreateNode(BTNodeType::Composite));
    sequencer1->SetCompositeType(BTNodeCompositeType::Sequencer);
    treeEditor->CreateLink(selector1->GetChildrenAttributeId(), sequencer1->GetParentAttributeId());

    auto MoveTo1 = static_cast<BTEditorNodeLogic*>(treeEditor->CreateNode(BTNodeType::Logic));
    MoveTo1->SetLogicType(BTNodeLogicType::MoveTo);
    treeEditor->CreateLink(selector1->GetChildrenAttributeId(), MoveTo1->GetParentAttributeId());

    auto MoveTo2 = static_cast<BTEditorNodeLogic*>(treeEditor->CreateNode(BTNodeType::Logic));
    MoveTo2->SetLogicType(BTNodeLogicType::MoveTo);
    treeEditor->CreateLink(sequencer1->GetChildrenAttributeId(), MoveTo2->GetParentAttributeId());

    BehaviorTreeGame* treeGame = new BehaviorTreeGame(nullptr, treeEditor);

    auto s = treeGame->GetRootNode();
    std::cout << "\n";
}
