#include "config.h"
#include <cstddef>
#include <filesystem>
#include <iostream>
#include <string>
#include <yaml-cpp/yaml.h>

using std::string;

Config::Config(const string *path) {
    // Null check
    if (!path) {
        std::cout << "Warning: Config string is null. Resulting to default" << std::endl;
        this->defaults();
        return;
    }

    const std::filesystem::path p(*path);

    // Check config file exists
    if (!std::filesystem::exists(p)) {
        std::cout << "Warning: Config file not found. Resulting to default" << std::endl;
        this->defaults();
        return;
    }

    const YAML::Node config = YAML::LoadFile(p);
    
    runner = config["runner"].as<string>();
    return;
}

void Config::defaults() {
    this->runner = "fzf";
    this->bookmarks = NULL;
}
