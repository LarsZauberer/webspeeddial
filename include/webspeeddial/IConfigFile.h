#ifndef IConfigLoader_h_INCLUDED
#define IConfigLoader_h_INCLUDED

#include "webspeeddial/INode.h"
namespace core {

/**@brief Abstract class for config loading
 */

class IConfigFile {
public:
  virtual ~IConfigFile() = default;

  virtual INode* read();
  virtual void write(INode*);
  virtual bool file_exists();
};

}; // namespace core

#endif // IConfigLoader_h_INCLUDED
