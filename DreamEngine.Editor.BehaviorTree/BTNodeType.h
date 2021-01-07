#pragma once

#include <map>
#include <string>

enum class BTNodeType
{
    Root,
    Composite,
    Logic,

    UNKNOWN
};

enum class BTNodeCompositeType
{
    Sequencer,
    Selector
};

const std::map<BTNodeType, std::string> MAP_NODE_TYPE_TO_STRING = {
    { BTNodeType::Composite, "Composite" },
    { BTNodeType::Logic, "Logic" },
};

const std::map<BTNodeCompositeType, std::string> MAP_NODE_COMPOSITE_TYPE_TO_STRING = {
    { BTNodeCompositeType::Sequencer, "Sequencer" },
    { BTNodeCompositeType::Selector, "Selector" },
};
