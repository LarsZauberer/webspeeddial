#include "webspeeddial/ConfigManager.h"
#include "webspeeddial/Config.h"
#include "webspeeddial/IConfigFile.h"
#include "webspeeddial/INode.h"
#include "webspeeddial/YamlNode.h"
#include "yaml-cpp/node/node.h"
#include <iostream>
#include <string>
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
            this->create_default_config();
            this->cfg = default_config();
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

    void ConfigManager::create_default_config() {
            Config c = this->default_config();

            std::vector<INode*> bm_nodes;
            bm_nodes.reserve(32);

            INode *node = new YamlNode();
            INode *bookmarks_node = new YamlNode();
            bm_nodes.push_back(node);
            bm_nodes.push_back(bookmarks_node);

            node->set("Runner", c.runner);
            node->set("Bookmarks", *bookmarks_node);
            for (size_t i = 0; i < c.bookmarks.size(); i++) {
                if (!c.bookmarks[i]) {
                    continue;
                }
                INode *bm = new YamlNode();
                bm_nodes.push_back(bm);
                bm->set("Name", c.bookmarks[i]->name);
                bm->set("Link", c.bookmarks[i]->link);
                node->get("Bookmarks")->push_back(*bm);
            }

            YamlNode *ynode = new YamlNode(node);
            cf->write(ynode);
    }
};
