#include "webspeeddial/ConfigManager.h"
#include "webspeeddial/Config.h"
#include "webspeeddial/IConfigFile.h"
#include "webspeeddial/INode.h"
#include "webspeeddial/YamlNode.h"
#include "webspeeddial/utils.h"
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
        unalloc_all(cfg.bookmarks);
    };

    const Config *ConfigManager::get_config() {return &cfg;};

    void ConfigManager::load() {
        if (!cf) {
            return;
        }

        if (!cf->file_exists()) {
            std::cout << "Warning: No config file found" << std::endl;
            this->cfg = default_config();
            this->write();
            return;
        }

        INode *node = cf->read();
        if (this->is_valid(node)) {
            std::cout << "Error: Config has invalid webspeeddial format. Default config will be loaded" << std::endl;
            this->cfg = default_config();
            return;
        };

        this->parse(node);
        delete node;
        return;
    };

    Config ConfigManager::default_config() {
        std::vector<BookMark*> vec; 
        return {
            "fzf",
            vec
        };
    }

    void ConfigManager::write() {
            std::vector<INode*> nodes_to_delete;
            nodes_to_delete.reserve(32);

            INode *node = new YamlNode();
            INode *bookmarks_node = new YamlNode();
            nodes_to_delete.push_back(node);
            nodes_to_delete.push_back(bookmarks_node);

            node->set("Runner", cfg.runner);
            node->set("Bookmarks", *bookmarks_node);
            for (size_t i = 0; i < cfg.bookmarks.size(); i++) {
                if (!cfg.bookmarks[i]) {
                    continue;
                }
                INode *bm = new YamlNode();
                nodes_to_delete.push_back(bm);
                bm->set("Name", cfg.bookmarks[i]->name);
                bm->set("Link", cfg.bookmarks[i]->link);
                node->get("Bookmarks")->push_back(*bm);
            }

            cf->write(node);

            unalloc_all(nodes_to_delete);
    }

    bool ConfigManager::is_valid(const INode *node) {
        std::cout << "Debug: `core::ConfigManager::is_valid` is not implemented";
        return true;
    }

    void ConfigManager::parse(const INode *node) {
        std::cout << "Debug: `core::ConfigManager::parse` is not implemented";
        this->cfg = default_config();
    }
};
