#ifndef IConfigManager_h_INCLUDED
#define IConfigManager_h_INCLUDED

#include "webspeeddial/Config.h"
#include <vector>

namespace core {

/**@brief An abstract class describing a config manager that loads a config form a file, checks the validity, writes back the default config etc.
 */

class IConfigManager {
    public:
        virtual ~IConfigManager() = default;

        virtual const Config *get_config() {return nullptr;};
        virtual void load() {};
        virtual void write() {};
};

};

#endif // IConfigManager_h_INCLUDED
