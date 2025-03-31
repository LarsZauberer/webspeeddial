#ifndef YamlConfigFile_h_INCLUDED
#define YamlConfigFile_h_INCLUDED

#include "webspeeddial/IConfigFile.h"
#include <filesystem>
#include <optional>
namespace core {
class YamlConfigFile : public IConfigFile {
public:
  YamlConfigFile();
  YamlConfigFile(std::filesystem::path path);
  ~YamlConfigFile();

  INode *read();
  void write(INode *);
  bool file_exists();

private:
  std::filesystem::path file;
  std::filesystem::path dirs;

  std::optional<std::filesystem::path> get_default_path();
  void create_dirs();
  bool dirs_exist();
};
} // namespace core

#endif // YamlConfigFile_h_INCLUDED
