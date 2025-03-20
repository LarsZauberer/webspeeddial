#include <iostream>
#include <cstdarg>
#include <cstdio>

#include "config.h"
#include "commands.h"
#include "utils.h"

int main() {
    BookMark test = {"test", "https://thealternative.ch"};
    BookMark bookmarks[] = {test};
    Config cfg = {"fzf", bookmarks};

    string selector_string = bookmarks_to_fzf(&cfg.bookmarks, 1); 

    string selected = runner(&cfg.runner, &selector_string); 

    // Remove trailing \n
    remove_trailing(&selected); 

    // Find string in bookmarks
    BookMark* selected_bookmark = find_name(&selected, &cfg.bookmarks, 1);
    if (!selected_bookmark) {
        std::cout << "Selected bookmark is not in the bookmarks list" << std::endl;
        return 1;
    }
    xdg_open(&selected_bookmark->link); 
    return 0;
}
