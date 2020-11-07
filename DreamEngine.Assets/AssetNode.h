#pragma once

#include <string>
#include <vector>

class Node
{
    struct NodeStruct
    {
        std::string NodeName;
        Node* ParentNode;
        std::vector<Node*> ChildNode;
    };

    Node(std::string nodeName, Node* parentNode);

    
    NodeStruct nodeStruct;
};
