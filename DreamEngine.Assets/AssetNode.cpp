#include "AssetNode.h"

Node::Node(std::string nodeName, Node* parentNode)
{
    nodeStruct.NodeName = nodeName;
    nodeStruct.ParentNode = parentNode;
}

std::string Node::GetNodeName()
{
    return nodeStruct.NodeName;
}

Node* Node::GetParentNode()
{
    return nodeStruct.ParentNode;
}

std::vector<Node*> Node::GetChildNode()
{
    return  nodeStruct.ChildNode;
}

void Node::SetNodeName(std::string nodeName)
{
    nodeStruct.NodeName = nodeName;
}

void Node::SetParentNode(Node* parentNode)
{
    nodeStruct.ParentNode = parentNode;
}

void Node::SetChildNode(Node* childNode)
{
    nodeStruct.ChildNode.push_back(childNode);
}

void Node::SetChildNode(std::vector<Node*> childNodes)
{
    nodeStruct.ChildNode.insert(std::end(nodeStruct.ChildNode), std::begin(childNodes), std::end(childNodes));
}
