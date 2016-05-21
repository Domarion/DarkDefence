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
inline TreeNode<T>::~TreeNode()
{
}

template<typename T>
inline bool TreeNode<T>::addChild(string itemname, TreeNode<T>& item)
{

	children.insert(std::make_pair(itemname, item));


	return true;//TODO: ??
}

template<typename T>
inline bool TreeNode<T>::addChildData(string itemname, T& nodeData)
{
    TreeNode<T>* item = new TreeNode<T>("itemname", this->getNodeName(), nodeData);
    return addChild(itemname, *item);
}



template<typename T>
inline bool TreeNode<T>::removeChild(TreeNode<T>& item)//TODO:implement
{
	return false;

}


template<typename T>
inline bool TreeNode<T>::addChildtoParent(string parentname, string itemname,
		 TreeNode<T>& item)
{
	if (parentname == itemname)
		return false;

	if (nodeName == parentname)
		return addChild(itemname, item);

	 TreeNode<T>* someNode = recursiveSearch(parentname);
	 if (someNode == nullptr)
	 {
		 return false;
		// throw new exception("Error(NPE): Can't find parentNode");
	 }

	 return someNode->addChild(itemname, item);

}

/*template<typename T>
inline TreeNode<T>::TreeNode(string name, const T& newData)
:nodeName(name), data(newData)
{
}*/

template<typename T>
inline TreeNode<T>::TreeNode(string name, string parent_name, T& newData)
:nodeName(name), parentName(parent_name), data(newData)
{
}

template<typename T>
inline TreeNode<T>::TreeNode()
{

}

template<typename T>
inline const string& TreeNode<T>::getNodeName() const
{
	return nodeName;
}

template<typename T>
inline TreeNode<T>* TreeNode<T>::recursiveSearch(string itemname)
{
	if (nodeName == itemname)
		return this;

	for(auto ptr =  children.begin(); ptr != children.end(); ++ptr)
	{

        if (ptr->second.nodeName == itemname)
            return &(ptr->second);
        TreeNode<T>* someNode = ptr->second.recursiveSearch(itemname);
		if (someNode != nullptr)
			return someNode;
	}
	return nullptr;
}

template<typename T>
inline T& TreeNode<T>::getData()
{
	return data;
}
template<typename T>
void TreeNode<T>::setData(const T &value)
{
    data = value;
}

template<typename T>
map<std::__cxx11::string, TreeNode<T> > &TreeNode<T>::getChildren()
{
    return children;
}

template<typename T>
vector<std::__cxx11::string> TreeNode<T>::getChildrenNames()
{
    vector<string> keys;

    for(auto t = children.begin(); t!=children.end(); ++t)
    {
        keys.push_back(t->first);
    }
    return keys;
}
