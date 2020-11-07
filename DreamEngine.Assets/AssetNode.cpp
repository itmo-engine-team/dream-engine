#include "AssetNode.h"

Node::Node(std::string nodeName, Node* parentNode)
{
    nodeStruct.NodeName = nodeName;
    nodeStruct.ParentNode = parentNode;
}
