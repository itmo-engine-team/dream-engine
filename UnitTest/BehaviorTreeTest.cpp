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
    BehaviorTreeGame* tree = new BehaviorTreeGame();

    BTGameNodeSequence* sequence = new BTGameNodeSequence(tree->GetRootNode());

    BTGameNodeLogic* logic1 = new BTGameNodeLogic(sequence);
    logic1->result = true;

    BTGameNodeLogic* logic2 = new BTGameNodeLogic(sequence);
    logic2->result = false;

    BTGameNodeLogic* logic3 = new BTGameNodeLogic(sequence);
    logic3->result = true;

    bool result = tree->Update();

    std::cout << result << "\n";
    std::cout << sequence->iterator;
}

TEST(BehaviorTreeTest, SelectorTest)
{
    BehaviorTreeGame* tree = new BehaviorTreeGame();

    BTGameNodeSelector* selector = new BTGameNodeSelector(tree->GetRootNode());

    BTGameNodeLogic* logic1 = new BTGameNodeLogic(selector);
    logic1->result = false;

    BTGameNodeLogic* logic2 = new BTGameNodeLogic(selector);
    logic2->result = false;

    BTGameNodeLogic* logic3 = new BTGameNodeLogic(selector);
    logic3->result = true;
   
    bool result = tree->Update();

    std::cout << result << "\n";
    std::cout << selector->iterator;
}