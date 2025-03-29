#include "webspeeddial/config.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <pwd.h>
#include <unistd.h>
#include <vector>
#include <yaml-cpp/emitter.h>
#include <yaml-cpp/emittermanip.h>
#include <yaml-cpp/node/node.h>
#include <yaml-cpp/node/parse.h>
#include <yaml-cpp/yaml.h>

namespace core {

std::filesystem::path *get_home() {
  int uid = getuid();
  struct passwd *pw = getpwuid(uid);

  return new std::filesystem::path(pw->pw_dir);
}

std::filesystem::path *get_default_path() {
  std::filesystem::path *p = get_home();
  if (!p) {
    std::cout << "Error: Couldn't acquire the home directory" << std::endl;
    return NULL;
  }

  // Check existance of home
  if (!std::filesystem::exists(*p)) {
    std::cout << "Error: Faulty home path" << std::endl;
    return NULL;
  }

  // .config folder
  *p /= std::filesystem::path(".config");
  if (!std::filesystem::exists(*p)) {
    std::cout << "Warning: Creating .config folder" << std::endl;
    std::filesystem::create_directory(*p);
  }

  // Webspeeddial folder
  *p /= std::filesystem::path("webspeeddial");
  if (!std::filesystem::exists(*p)) {
    std::cout << "Warning: Creating webspeeddial folder" << std::endl;
    std::filesystem::create_directory(*p);
  }

  *p /= std::filesystem::path("config.yaml");

  return p;
}

void Config::create_default_file() {
  this->defaults();

  YAML::Emitter out;
  out << YAML::BeginMap;
  out << YAML::Key << "Runner" << YAML::Value << "fzf";
  out << YAML::Key << "Bookmarks" << YAML::BeginSeq;
  for (size_t i = 0; i < this->bookmarks.size(); i++) {
    out << YAML::BeginMap;
    out << YAML::Key << "Name" << YAML::Value << this->bookmarks[i]->name;
    out << YAML::Key << "Link" << YAML::Value << this->bookmarks[i]->link;
    out << YAML::EndMap;
  }
  out << YAML::EndSeq;

  std::ofstream cfile(*this->path);
  cfile << out.c_str();
  cfile.close();

  return;
}

void Config::loader() {
  std::cout << "Loading config at: " << *this->path << std::endl;
  YAML::Node node = YAML::LoadFile(*this->path);
  if (node["Runner"].IsDefined()) {
    this->runner = node["Runner"].as<std::string>();
  } else {
    std::cout << "Warning: Runner Key not set. Defaulting to fzf" << std::endl;
    this->runner = "fzf";
  }
  this->bookmarks = std::vector<BookMark *>();
  YAML::Node bm = node["Bookmarks"];
  if (bm.IsDefined() && bm.IsSequence()) {
    for (size_t i = 0; i < bm.size(); i++) {
      const auto ele = bm[i];
      if (!ele["Name"].IsDefined()) {
        std::cout << "Warning: Bookmark " << i + 1 << " has no valid `Name`"
                  << std::endl;
        continue;
      }
      if (!ele["Link"].IsDefined()) {
        std::cout << "Warning: Bookmark " << i + 1 << " has no valid `Link`"
                  << std::endl;
        continue;
      }
      BookMark *b = new BookMark{ele["Name"].as<std::string>(),
                                 ele["Link"].as<std::string>()};
      this->bookmarks.push_back(b);
    }
  } else {
    std::cout << "Warning: No Bookmarks defined" << std::endl;
  }
}

Config::Config() {
  this->path = get_default_path();
  if (!this->path) {
    std::cout << "Error: Critical error while loading config" << std::endl;
    return;
  }

  if (!std::filesystem::exists(*this->path)) {
    std::cout << "Warning: Config file doesn't exist. Creating one from scratch"
              << std::endl;
    this->create_default_file();
    return;
  }

  this->loader();
}

Config::Config(std::string path) {
  this->path = new std::filesystem::path(path);
  if (!this->path) {
    std::cout << "Error: Critical error while loading config" << std::endl;
    return;
  }

  this->loader();
}

void Config::defaults() {
  this->runner = "fzf";
  BookMark *b = new BookMark{"Webspeeddial",
                             "https://github.com/LarsZauberer/webspeeddial"};
  this->bookmarks = std::vector<BookMark *>({b});
}

Config::~Config() {
  delete this->path;

  for (size_t i = 0; i < this->bookmarks.size(); i++) {
    delete this->bookmarks[i];
  }
};

}; // namespace core
