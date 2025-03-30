#ifndef ConfigManager_h_INCLUDED
#define ConfigManager_h_INCLUDED

#include "webspeeddial/IConfigFile.h"
#include "webspeeddial/IConfigManager.h"
namespace core {

/**@brief The real implementation of the ConfigManager. It manages a YAML file
 */

class ConfigManager : public IConfigManager {
    public:
        ConfigManager(IConfigFile *cf);
        ~ConfigManager();

        const Config &get_config();
        void read();
    private:
        IConfigFile *cf;
        Config cfg;

        bool check_validity();
        Config default_config();
        void write_default_config();
};

};

#endif // ConfigManager_h_INCLUDED
