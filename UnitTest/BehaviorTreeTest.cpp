#include "pch.h"

#include <iostream>

#include "BehaviorTreeGame.h"
#include "BTGameNode.h"
#include "BTGameNodeRoot.h"
#include "BTGameNodeLogic.h"
#include "BTGameNodeSelector.h"
#include "BTGameNodeSequence.h"

TEST(BehaviorTreeTest, SequencerTest)
{
    BTGameNodeRoot* root = new BTGameNodeRoot(); 

    BTGameNodeSequence* sequence = new BTGameNodeSequence(root);

    BTGameNodeLogic* logic1 = new BTGameNodeLogic(sequence);
    logic1->result = true;
    BTGameNodeLogic* logic2 = new BTGameNodeLogic(sequence);
    logic2->result = false;
    BTGameNodeLogic* logic3 = new BTGameNodeLogic(sequence);
    logic3->result = true;

    sequence->SetChildren(std::vector<BTGameNode*>{ logic1, logic2, logic3 });
    root->SetChild(sequence);

    BehaviorTreeGame* tree = new BehaviorTreeGame(root);
    bool result = tree->Update();

    std::cout << result << "\n";
    std::cout << sequence->iterator;
}

TEST(BehaviorTreeTest, SelectorTest)
{
    BTGameNodeRoot* root = new BTGameNodeRoot();

    BTGameNodeSelector* selector = new BTGameNodeSelector(root);

    BTGameNodeLogic* logic1 = new BTGameNodeLogic(selector);
    logic1->result = false;
    BTGameNodeLogic* logic2 = new BTGameNodeLogic(selector);
    logic2->result = false;
    BTGameNodeLogic* logic3 = new BTGameNodeLogic(selector);
    logic3->result = true;

    selector->SetChildren(std::vector<BTGameNode*>{ logic1, logic2, logic3 });
    root->SetChild(selector);

    BehaviorTreeGame* tree = new BehaviorTreeGame(root);
    bool result = tree->Update();

    std::cout << result << "\n";
    std::cout << selector->iterator;
}