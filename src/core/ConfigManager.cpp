#include "webspeeddial/ConfigManager.h"
#include "webspeeddial/Config.h"
#include "webspeeddial/IConfigFile.h"
#include "webspeeddial/YamlNode.h"
#include "yaml-cpp/node/node.h"
#include <iostream>
#include <vector>
namespace core {
    ConfigManager::ConfigManager(IConfigFile *cf) : cf(cf) {};
    ConfigManager::~ConfigManager() {
        if (cf) {
            delete cf;
        }
    };

    const Config &ConfigManager::get_config() {return cfg;};

    void ConfigManager::read() {
        if (!cf) {
            return;
        }

        if (!cf->file_exists()) {
            std::cout << "Warning: No config file found" << std::endl;
            cf->create_dirs();
            this->write_default_config();
            return;
        }

        INode *node = cf->read();
        if (this->check_validity()) {
            std::cout << "Error: Config has invalid webspeeddial format. Default config will be loaded" << std::endl;
        };
    };

    Config ConfigManager::default_config() {
        std::vector<BookMark*> vec; 
        return {
            "fzf",
            vec
        };
    }

    void ConfigManager::write_default_config() {
            Config c = this->default_config();

            YAML::Node node;
            node["Runner"] = c.runner;
            for (size_t i = 0; i < c.bookmarks.size(); i++) {
                if (!c.bookmarks[i]) {
                    continue;
                }
                YAML::Node bm;
                bm["Name"] = c.bookmarks[i]->name;
                bm["Link"] = c.bookmarks[i]->link;
                node["Bookmarks"].push_back(bm);
            }

            YamlNode *ynode = new YamlNode(node);
            cf->write(ynode);
    }
};
