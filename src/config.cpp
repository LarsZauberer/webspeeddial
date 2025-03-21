#include "config.h"
#include <string>
#include <yaml-cpp/yaml.h>

using std::string;

Config::Config() {
    const YAML::Node config = YAML::LoadFile("/home/lars/.config/webspeeddial/config.yaml");
    
    runner = config["runner"].as<string>();
}
