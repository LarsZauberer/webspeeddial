#include <iostream>
#include <cstdarg>
#include <cstdio>

#include "config.h"
#include "commands.h"
#include "utils.h"

int main() {
    // BookMark test = {"test", "https://thealternative.ch"};
    // BookMark bookmarks[] = {test};
    const string config_path = "/home/lars/.config/webspeeddial/config.yaml";
    Config cfg(&config_path);

    std::cout << cfg.runner << std::endl;

    // string selector_string = bookmarks_to_fzf(&cfg.bookmarks, 0); 

    // string selected = runner(&cfg.runner, &selector_string); 

    // // Remove trailing \n
    // remove_trailing(&selected); 

    // // Find string in bookmarks
    // BookMark* selected_bookmark = find_name(&selected, &cfg.bookmarks, 0);
    // if (!selected_bookmark) {
    //     std::cout << "Selected bookmark is not in the bookmarks list" << std::endl;
    //     return 1;
    // }
    // xdg_open(&selected_bookmark->link); 
    // return 0;
}
