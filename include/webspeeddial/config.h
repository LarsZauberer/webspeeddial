#ifndef config_h_INCLUDED
#define config_h_INCLUDED

#include <string>
#include <vector>
namespace core {
    /**@brief A structure describing a bookmark
     */
    struct Bookmark{
        /**@brief The name of the bookmark. This is what is shown to the user when the user searches for a Bookmark
         */
        std::string name;

        /**@brief The link that is opened then the bookmark is selected
         */
        std::string link;
    };

    /**@brief A structure holding all the information about the bookmarks and the runner
     */
    struct Config {
        /**@brief The runner describes the fuzzy finder that is used to search for the bookmarks
         */
        std::string runner;

        /**@brief A vector owning and containing all the bookmarks
         */
        std::vector<Bookmark> bookmarks;
    };
}

#endif // config_h_INCLUDED
