#include "webspeeddial/YamlConfigFile.h"
#include "webspeeddial/YamlNode.h"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <optional>
#include <pwd.h>
#include <unistd.h>
namespace core {
YamlConfigFile::YamlConfigFile() {
  std::optional<std::filesystem::path> p_wrapped = this->get_default_path();
  if (!p_wrapped.has_value()) {
    std::cout
        << "Fatal Error: Failed to determine the home directory of the user"
        << std::endl;
    std::exit(1); // Panic
    return;
  }

  file = p_wrapped.value();
  dirs = p_wrapped.value().remove_filename();
  return;
};
YamlConfigFile::YamlConfigFile(std::filesystem::path path) : file(path) {
  dirs = path.remove_filename();
};

YamlConfigFile::~YamlConfigFile() {
}

INode *YamlConfigFile::read() {
  YAML::Node node = YAML::LoadFile(file);
  YamlNode *inode = new YamlNode(node);
  return inode;
}

void YamlConfigFile::write(INode *node) {
  if (!node) {
    std::cout << "Warning: Config given to YamlConfigFile was empty. Couldn't "
                 "write config file"
              << std::endl;
    return;
  }

  // Check directory existance
  if (!dirs_exist()) create_dirs();
 
  std::ofstream out(file);
  node->write(out);
  out.close();
}

bool YamlConfigFile::file_exists() { return std::filesystem::exists(file); }

void YamlConfigFile::create_dirs() {
  std::filesystem::create_directories(dirs);
}

bool YamlConfigFile::dirs_exist() {
    return std::filesystem::exists(dirs);
}

std::optional<std::filesystem::path> YamlConfigFile::get_default_path() {
  int uid = getuid();
  struct passwd *pw = getpwuid(uid);

  if (!pw) {
    return {};
  }

  return pw->pw_dir;
}
} // namespace core
