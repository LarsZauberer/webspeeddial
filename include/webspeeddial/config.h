#ifndef config_h_INCLUDED
#define config_h_INCLUDED

#include <filesystem>
#include <stdlib.h>
#include <string>
#include <vector>

namespace core {

/*@file config.h Describes all the datastructures for the config file needed. It
 * also handles all the I/O from the config file.
 */

/**@brief A structure describing the relation of a `name` and a `link`.
 */

struct BookMark {
  /**@brief The name of the BookMark
   */

  std::string name;

  /**@brief The link corresponding to the BookMark
   */

  std::string link;
};

/**@brief The config of Webspeeddial
 *
 * It contains all the information about what selection program it should use
 * and what are all the bookmarks
 */

class Config {
public:
  /**@brief Default constructor for Config
   *
   * It will try to find a Config file in the xdg config path. If non exist it
   * will create a config with default values.
   */

  Config();

  /**@brief Creates a Config object with a certain config file path
   *
   * It will automatically load the config file from this path
   *
   * @param path The path to the config file. It is *copied by value*
   */

  Config(std::string path);

  /**@brief Destructor for the Config. It will delete everything it has to
   * delete.
   * @note All the BookMark objects will be deleted too.
   */

  ~Config();

  /**@brief Returns the selection runner
   */

  std::string *get_runner() { return &runner; };

  /**@brief Returns the collection of bookmarks
   */

  std::vector<BookMark *> *get_bookmarks() { return &bookmarks; };

private:
  std::filesystem::path *path;
  std::string runner;
  std::vector<BookMark *> bookmarks;

  void create_default_file();
  void loader();
  void defaults();
};

}; // namespace core

#endif // config_h_INCLUDED
