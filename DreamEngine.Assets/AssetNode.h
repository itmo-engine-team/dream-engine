#pragma once

#include <string>
#include <vector>

class Node
{

public:

    struct NodeStruct
    {
        std::string NodeName;
        Node* ParentNode;
        std::vector<Node*> ChildNode;
    };

    Node(std::string nodeName, Node* parentNode);

    std::string GetNodeName();
    Node* GetParentNode();
    std::vector<Node*> GetChildNode();

    void SetNodeName(std::string nodeName);
    void SetParentNode(Node* parentNode);
    void SetChildNode(Node* childNode);
    void SetChildNode(std::vector<Node*> childNodes);

private:

    NodeStruct nodeStruct;
};
