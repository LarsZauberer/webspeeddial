#include "webspeeddial/YamlConfigFile.h"
#include "webspeeddial/YamlNode.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <pwd.h>
#include <unistd.h>
namespace core {
    YamlConfigFile::YamlConfigFile() {
      int uid = getuid();
      struct passwd *pw = getpwuid(uid);

      if (!pw) {
          path = NULL;
          return;
      }

        path = std::filesystem::path(pw->pw_dir);
    };
    YamlConfigFile::YamlConfigFile(std::filesystem::path path) : path(path) {};

    YamlConfigFile::~YamlConfigFile() {
        if (!main_node) {
            return;
        }
        delete main_node;
    }

    INode *YamlConfigFile::read() {
        YAML::Node node = YAML::LoadFile(path); 
        YamlNode *inode = new YamlNode(node);
        main_node = inode;
        return inode;
    }

    void YamlConfigFile::write(INode *node) {
        if (!node) {
            std::cout << "Warning: Config given to YamlConfigFile was empty. Couldn't write config file" << std::endl;
        }

        main_node = node;

        std::ofstream out(path);
        node->write(out);
        out.close();
    }

    bool YamlConfigFile::file_exists() {
        return std::filesystem::exists(path);
    }

    void YamlConfigFile::create_dirs() {
        std::filesystem::path dir_path = path; // Copy
        dir_path.remove_filename();
        std::filesystem::create_directories(dir_path); 
    }
}
