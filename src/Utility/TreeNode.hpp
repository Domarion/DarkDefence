/*
 * TreeNode.h
 *
 *  Created on: 16 апр. 2016 г.
 *      Author: kostya_hm
 */

#pragma once

#include <cereal/access.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/tuple.hpp>
#include <vector>

using std::string;
using std::map;
using std::vector;

template<typename T>
class TreeNode : public std::enable_shared_from_this<TreeNode<T>>
{
    friend class cereal::access;
    template<class Archive>
    void serialize(Archive& ar, const unsigned int /*version*/)
    {
        ar(CEREAL_NVP(nodeName), cereal::make_nvp("nodeData",data), CEREAL_NVP(children));
    }

public:

    TreeNode(const std::string& aNodeName, std::unique_ptr<T>&& aData);
    TreeNode(const std::string& aNodeName, std::shared_ptr<T>&& aData);

    TreeNode() = default;
    ~TreeNode() = default;

    void addChild(std::unique_ptr<TreeNode<T>>&& aNode);
    void addChildData(const std::string& aNodeName, std::unique_ptr<T>&& aNodeData);
    bool addChildtoParent(const std::string& aParentName, std::unique_ptr<TreeNode<T>>&& aNode);

    std::shared_ptr<TreeNode<T>> recursiveSearch(const std::string& itemname);

    const std::shared_ptr<T>& getData() const;
    void setData(const std::shared_ptr<T>& aData);
    void setData(std::shared_ptr<T>&& aData);

    const string& getNodeName() const;
    const auto& getChildren() const;
    vector<string> getChildrenNames();
    bool hasChildren() const;

private:
    string nodeName;
    std::shared_ptr<T> data;
    map<string, std::shared_ptr<TreeNode<T>>> children;
};

#include "../Utility/TreeNode_impl.hpp"





