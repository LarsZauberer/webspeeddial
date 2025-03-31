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
        void load();
        void write();
    private:
        // Owned
        IConfigFile *cf;
        Config cfg;

        Config default_config();
        bool is_valid(const INode *node);
        void parse(const INode *node);
};

};

#endif // ConfigManager_h_INCLUDED
