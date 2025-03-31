#ifndef YamlNode_h_INCLUDED
#define YamlNode_h_INCLUDED

#include "webspeeddial/INode.h"
#include "yaml-cpp/node/node.h"
#include <fstream>
namespace core {

/**
 * @brief Implementation of the INode interface with the YAML::Node
 */

class YamlNode : public INode {
public:
  YamlNode();
  YamlNode(YAML::Node node);
  ~YamlNode();

  bool is_defined();
  bool is_sequence();
  std::string as_string();
  INode *get(std::string &&key);
  void set(std::string &&key, INode &node);
  void set(std::string &&key, std::string &value);
  void push_back(INode &&node);
  void push_back(std::string &&value);
  void write(std::ofstream &out);

private:
  YAML::Node node;
  std::vector<INode *> sub_nodes;
};
}; // namespace core

#endif // YamlNode_h_INCLUDED
