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

  virtual bool is_defined() {return false;};
  virtual bool is_sequence() {return false;};
  virtual std::string as_string() {return "";};
  virtual INode *get(std::string &&key) {return nullptr;};
  virtual INode *get(size_t i) {return nullptr;};
  virtual void set(std::string &&key, INode &node) {};
  virtual void set(std::string &&key, std::string &value) {};
  virtual void push_back(INode &node) {};
  virtual void push_back(std::string &value) {};
  virtual void write(std::ofstream &out) {};
};

}; // namespace core

#endif // ConfigFile_h_INCLUDED
