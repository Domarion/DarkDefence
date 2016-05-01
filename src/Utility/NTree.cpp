#include "NTree.h"
/*
NTree::NTree()
{

}


bool NTree::addNode(MobModel* value, string parentName)
{
    if (value == nullptr)
        return false;

    if (parentName == "none")
    {
       rootNode.setData(*value);
       return true;
    }

    TreeNode<MobModel>*parentNode = const_cast< TreeNode<MobModel>* >(findNodeByName(parentName));
    //(string name, string parent_name, T& newData)
    TreeNode<MobModel>* newNode = new TreeNode<MobModel>(value->getName(), parentName, *value);


    return parentNode->addChild(value->getName(), *newNode);
}

bool NTree::removeNode(MobModel* value)
{
    return false;
}

MobModel* NTree::getRootData()
{
    return &rootNode.getData();
}

MobModel* NTree::getDataByNodeName(std::string name)
{
    return &findNodeByName(name)->getData();
}

const TreeNode<MobModel>* NTree::findNodeByName(std::string name)
{

    return rootNode.recursiveSearch(name);
}
*/
