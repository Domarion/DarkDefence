/*
 * TreeNode.h
 *
 *  Created on: 16 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

//#include <boost/serialization/string.hpp>
//#include <boost/serialization/shared_ptr.hpp>

//#include <boost/serialization/version.hpp>
//#include <boost/serialization/utility.hpp>
//#include <boost/serialization/map.hpp>
//#include <boost/serialization/split_member.hpp>

#include <cereal/access.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/tuple.hpp>

using std::string;
using std::map;
#include <vector>
using std::vector;

template<typename T>
class TreeNode : public std::enable_shared_from_this<TreeNode<T>>
{
    friend class cereal::access;
	template<class Archive>
    void save(Archive & ar, const unsigned int /*version*/) const
	{
        ar(nodeName, parentName, data, children);
	}

    template<class Archive>
    void load(Archive & ar, const unsigned int /*version*/)
    {
        ar(nodeName, parentName, data, children);
    }

public:
	//TreeNode(string name, const T& newData);
    TreeNode(std::string name, std::string parent_name, std::unique_ptr<T> newData);
    TreeNode(std::string name, std::string parent_name, std::shared_ptr<T> newData);

    TreeNode();
	~TreeNode();
    bool addChild(string itemname, std::unique_ptr<TreeNode<T> >&& item);
    bool addChildData(string itemname, std::unique_ptr<T> nodeData);
    bool addChildtoParent(const std::string& parentname, const std::string& itemname, std::unique_ptr<TreeNode<T> >&& item);
//    bool removeChild(TreeNode<T>& item);
    std::shared_ptr<TreeNode<T> > recursiveSearch(string itemname);
    std::shared_ptr<T> getData();
    void setData(std::shared_ptr<T> value);
	const string& getNodeName() const;
    auto getChildren();
    vector<string> getChildrenNames();
    bool hasChildren() const;

private:
	string nodeName;
	string parentName;
    std::shared_ptr<T> data;
    map<string, std::shared_ptr<TreeNode<T>>> children;
};

#include "../Utility/TreeNode_impl.hpp"





