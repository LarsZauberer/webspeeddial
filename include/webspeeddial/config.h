#ifndef config_h_INCLUDED
#define config_h_INCLUDED

#include <string>
#include <vector>
namespace core {
/**@brief A structure describing a bookmark
 */
struct Bookmark {
  /**@brief The name of the bookmark. This is what is shown to the user when the
   * user searches for a Bookmark
   */
  std::string name;

  /**@brief The link that is opened then the bookmark is selected
   */
  std::string link;

  /**@brief Default constructor
   */
  Bookmark(std::string name, std::string link) : name(name), link(link) {};

  /**@brief Move constructor
   */
  Bookmark(Bookmark &&bm)
      : name(std::move(bm.name)), link(std::move(bm.link)) {};

  /**@brief Move assignment
   */
  Bookmark& operator=(Bookmark&& other) {
      this->name = std::move(other.name);
      this->link = std::move(other.link);
      return *this;
  };
};

/**@brief A structure holding all the information about the bookmarks and the
 * runner
 */
struct Config {
  /**@brief The runner describes the fuzzy finder that is used to search for the
   * bookmarks
   */
  std::string runner;

  /**@brief A vector owning and containing all the bookmarks
   */
  std::vector<Bookmark> bookmarks;

  /**@brief Move constructor
   */
  Config(Config &&cfg) : runner(std::move(cfg.runner)) {
    bookmarks = std::move(cfg.bookmarks);
  };
};
} // namespace core

#endif // config_h_INCLUDED
