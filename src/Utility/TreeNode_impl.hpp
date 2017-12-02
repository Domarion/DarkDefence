/*
 * TreeNode_impl.hpp
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include "../Utility/TreeNode.hpp"

template<typename T>
inline TreeNode<T>::TreeNode(const std::string& aNodeName, std::unique_ptr<T>&& aData)
    : nodeName(aNodeName)
    , data(std::move(aData))
{
}

template<typename T>
inline TreeNode<T>::TreeNode(const std::string& aNodeName, std::shared_ptr<T>&& aData)
    : nodeName(aNodeName)
    , data(std::move(aData))
{
}

template<typename T>
inline void TreeNode<T>::addChild(std::unique_ptr<TreeNode<T>>&& aNode)
{
    std::string newNodeName = aNode->getNodeName();
    children.emplace(std::make_pair(std::move(newNodeName), std::move(aNode)));
}

template<typename T>
inline void TreeNode<T>::addChildData(const std::string& aNodeName, std::unique_ptr<T>&& aNodeData)
{
    addChild(std::make_unique<TreeNode<T>>(aNodeName, std::move(aNodeData)));
}

template<typename T>
inline bool TreeNode<T>::addChildtoParent(const std::string& aParentName, std::unique_ptr<TreeNode<T>>&& aNode)
{
    if (!aNode || aParentName == aNode->getNodeName())
    {
		return false;
    }

    if (nodeName == aParentName)
    {
        addChild(std::move(aNode));
        return true;
    }

     auto parentNodePtr = recursiveSearch(aParentName);
     if (!parentNodePtr)
	 {
		 return false;
	 }

     parentNodePtr->addChild(std::move(aNode));
     return true;
}

template<typename T>
inline const string& TreeNode<T>::getNodeName() const
{
	return nodeName;
}

template<typename T>
inline std::shared_ptr<TreeNode<T>> TreeNode<T>::recursiveSearch(const std::string& aItemName)
{
    if (aItemName.empty())
    {
        return nullptr;
    }

    if (nodeName == aItemName)
    {
        return std::enable_shared_from_this<TreeNode<T>>::shared_from_this();
    }

    for (const auto& child : children)
	{
        if (!child.second)
        {
            continue;
        }

        if (child.second->nodeName == aItemName)
        {
            return child.second;
        }

        auto someNode = child.second->recursiveSearch(aItemName);
        if (someNode)
        {
			return someNode;
        }
	}

	return nullptr;
}

template<typename T>
inline const std::shared_ptr<T>& TreeNode<T>::getData() const
{
	return data;
}

template<typename T>
void TreeNode<T>::setData(const std::shared_ptr<T>& aData)
{
    data = aData;
}

template<typename T>
void TreeNode<T>::setData(std::shared_ptr<T>&& aData)
{
    data = std::move(aData);
}

template<typename T>
const auto& TreeNode<T>::getChildren() const
{
    return children;
}

template<typename T>
vector<string> TreeNode<T>::getChildrenNames()
{
    vector<string> keys;

    for (auto t = children.begin(); t != children.end(); ++t)
    {
        keys.emplace_back(t->first);
    }

    return keys;
}

template<typename T>
bool TreeNode<T>::hasChildren() const
{
    return !children.empty();
}
