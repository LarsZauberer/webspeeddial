#ifndef IConfigManager_h_INCLUDED
#define IConfigManager_h_INCLUDED

#include "webspeeddial/Config.h"

namespace core {

/**@brief An abstract class describing a config manager that loads a config form a file, checks the validity, writes back the default config etc.
 */

class IConfigManager {
    public:
        virtual ~IConfigManager() = default;

        virtual const Config &get_config() = 0;
        virtual void load() = 0;
        virtual void write() = 0;
};

};

#endif // IConfigManager_h_INCLUDED
