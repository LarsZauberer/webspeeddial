#ifndef ConfigFile_h_INCLUDED
#define ConfigFile_h_INCLUDED

#include <string>
namespace core {

/**@brief An abstract class describing a configuration file that can be loaded
 * by Config
 */
class INode {
public:
  virtual ~INode() = default;

  virtual bool is_defined() = 0;
  virtual bool is_sequence() = 0;
  virtual std::string as_string() = 0;
  virtual INode *get(std::string &&key) = 0;
  virtual void set(std::string &&key, INode &node) = 0;
  virtual void set(std::string &&key, std::string &value) = 0;
  virtual void push_back(INode &&node) = 0;
  virtual void push_back(std::string &&value);
  virtual void write(std::ofstream &out) = 0;
};

}; // namespace core

#endif // ConfigFile_h_INCLUDED
