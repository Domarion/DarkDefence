/*
 * TreeNode.h
 *
 *  Created on: 16 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <boost/serialization/access.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/utility.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/split_member.hpp>

#include <string>
using std::string;
#include <map>
using std::map;
#include <vector>
using std::vector;

template<typename T>
class TreeNode
{
	friend class boost::serialization::access;
	template<class Archive>
	void save(Archive & ar, const unsigned int version) const
	{
		ar & BOOST_SERIALIZATION_NVP(nodeName);
		ar & BOOST_SERIALIZATION_NVP(parentName);
		ar & BOOST_SERIALIZATION_NVP(data);


        ar & boost::serialization::make_nvp("children", children);



	/*	for(auto t = children.begin(); t != children.end(); ++t)
		{
			ar & boost::serialization::make_nvp("parentName", nodeName);
			t->second.save(ar, version);
		}*/
	}

	template<class Archive>
	void load(Archive & ar, const unsigned int version)
	{
		//ar & BOOST_SERIALIZATION_NVP(nodeName);
		//ar & BOOST_SERIALIZATION_NVP(data);

		ar & BOOST_SERIALIZATION_NVP(nodeName);
		ar & BOOST_SERIALIZATION_NVP(parentName);
		ar & BOOST_SERIALIZATION_NVP(data);
        ar & boost::serialization::make_nvp("children", children);

	}

	BOOST_SERIALIZATION_SPLIT_MEMBER()
public:
	//TreeNode(string name, const T& newData);
	TreeNode(string name, string parent_name, T& newData);
	TreeNode();
	~TreeNode();
	bool addChild(string itemname, TreeNode<T>& item);
    bool addChildData(string itemname, T& nodeData);
	bool addChildtoParent(string parentname, string itemname, TreeNode<T>& item);
	bool removeChild(TreeNode<T>& item);
    TreeNode<T>* recursiveSearch(string itemname);
    T& getData();
    void setData(const T& value);
	const string& getNodeName() const;
    map<string, TreeNode<T> > & getChildren();
    vector<string> getChildrenNames();

private:
	string nodeName;
	string parentName;
	T data;
	map<string, TreeNode<T> > children;
};

#include "../Utility/TreeNode_impl.hpp"



