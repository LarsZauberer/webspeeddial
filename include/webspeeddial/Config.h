#ifndef config_h_INCLUDED
#define config_h_INCLUDED

#include <stdlib.h>
#include <string>
#include <vector>

namespace core {

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

struct Config {
    /**@brief The Runner being used to select a bookmark
     */

  std::string runner;

  /**@brief The Bookmarks that can be selected
   */

  std::vector<BookMark *> bookmarks;
};

}; // namespace core

#endif // config_h_INCLUDED
