/*
 * TreeNode_impl.hpp
 *
 *  Created on: 17 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once


#include "../Utility/TreeNode.hpp"
//#include <exception>
//using std::exception;

template<typename T>
inline TreeNode<T>::TreeNode(std::string name, std::string parent_name, std::shared_ptr<T> newData)
    : nodeName(name)
    , parentName(parent_name)
    , data(newData)
{
}

template<typename T>
inline TreeNode<T>::TreeNode(std::string name, std::string parent_name, std::unique_ptr<T> newData)
    : nodeName(name)
    , parentName(parent_name)
    , data(std::move(newData))
{
}

template<typename T>
inline TreeNode<T>::~TreeNode()
{
}

template<typename T>
inline bool TreeNode<T>::addChild(string itemname, std::unique_ptr<TreeNode<T>>&& item)
{

    children.emplace(std::make_pair(itemname, std::move(item)));


	return true;//TODO: ??
}

template<typename T>
inline bool TreeNode<T>::addChildData(string itemname, std::unique_ptr<T> nodeData)
{
    auto item = std::make_unique<TreeNode<T>>(itemname, this->getNodeName(), std::move(nodeData));
    return addChild(itemname, std::move(item));
}



//template<typename T>
//inline bool TreeNode<T>::removeChild(TreeNode<T> &item)//TODO:implement
//{
//	return false;

//}


template<typename T>
inline bool TreeNode<T>::addChildtoParent(const string& parentname, const string& itemname,
         std::unique_ptr<TreeNode<T>>&& item)
{
	if (parentname == itemname)
		return false;

	if (nodeName == parentname)
        return addChild(itemname, std::move(item));

     auto someNode = recursiveSearch(parentname);
	 if (someNode == nullptr)
	 {
		 return false;
	 }

     return someNode->addChild(itemname, std::move(item));

}




template<typename T>
inline TreeNode<T>::TreeNode()
    : nodeName()
    , parentName()
    , data(std::make_shared<T>())
    , children()
{

}

template<typename T>
inline const string& TreeNode<T>::getNodeName() const
{
	return nodeName;
}

template<typename T>
inline std::shared_ptr<TreeNode<T>> TreeNode<T>::recursiveSearch(string itemname)
{
	if (nodeName == itemname)
        return std::enable_shared_from_this<TreeNode<T>>::shared_from_this();

    for(const auto& child : children)
	{

        if (child.second->nodeName == itemname)
            return child.second;
        auto someNode = child.second->recursiveSearch(itemname);
		if (someNode != nullptr)
			return someNode;
	}
	return nullptr;
}

template<typename T>
inline std::shared_ptr<T> TreeNode<T>::getData()
{
	return data;
}
template<typename T>
void TreeNode<T>::setData(std::shared_ptr<T> value)
{
    data = value;
}

template<typename T>
auto TreeNode<T>::getChildren()
{
    return children;
}

template<typename T>
vector<string> TreeNode<T>::getChildrenNames()
{
    vector<string> keys;

    for(auto t = children.begin(); t != children.end(); ++t)
    {
        keys.push_back(t->first);
    }
    return keys;
}


template<typename T>
bool TreeNode<T>::hasChildren() const
{
    return (!children.empty());
}
