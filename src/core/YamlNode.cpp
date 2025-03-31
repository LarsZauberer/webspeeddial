#include "webspeeddial/YamlNode.h"
#include "yaml-cpp/node/node.h"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <vector>
namespace core {
    YamlNode::YamlNode() {
        this->node = YAML::Node();
    }
    YamlNode::YamlNode(YAML::Node node) {
        this->node = node;
        sub_nodes = std::vector<INode*>();
        sub_nodes.reserve(4);
    }

    YamlNode::~YamlNode() {
        for (size_t i = 0; i < sub_nodes.size(); i++) {
            delete sub_nodes[i];
        }
    }

    bool YamlNode::is_defined() {
        return node.IsDefined();
    }

    bool YamlNode::is_sequence() {
        return node.IsSequence();
    }

    std::string YamlNode::as_string() {
        return node.as<std::string>();
    }

    INode *YamlNode::get(std::string &&key) {
        YamlNode *n = new YamlNode(node[key]);
        sub_nodes.push_back(n);
        return n;
    }

    INode *YamlNode::get(size_t i) {
        YamlNode *n = new YamlNode(node[i]);
        sub_nodes.push_back(n);
        return n;
    }

    void YamlNode::set(std::string &&key, INode &node) {
        this->node[key] = node;
    }

    void YamlNode::set(std::string &&key, std::string &value) {
        this->node[key] = value;
    }

    void YamlNode::push_back(INode &node) {
        this->node.push_back(node);
    }

    void YamlNode::push_back(std::string &value) {
        this->node.push_back(value);
    }

    void YamlNode::write(std::ofstream &out) {
        std::cout << "Debug: `core::YamlNode::write` is not implemented" << std::endl;
        return;
    }
}
