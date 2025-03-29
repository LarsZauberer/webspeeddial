#include <iostream>
#include <cstdarg>
#include <cstdio>
#include "webspeeddial/Runner.h"
#include "webspeeddial/utils.h"
#include "webspeeddial/commands.h"
#include "webspeeddial/config.h"

int main() {
    Config cfg = Config();

    std::string selector_string = bookmarks_to_fzf(cfg.get_bookmarks()); 
    std::string select_cmd = "echo " + selector_string + " | " + *cfg.get_runner();
    std::string runner_error = "Error: While running the runner " + *cfg.get_runner();

    Runner selecter(&select_cmd, &runner_error);

    std::string *selected_str = run_cmd(&selecter);
    remove_trailing(selected_str);

    // // Find string in bookmarks
    BookMark* selected_bookmark = find_name(selected_str, cfg.get_bookmarks());
    if (!selected_bookmark) {
        std::cout << "Selected bookmark is not in the bookmarks list" << std::endl;
        delete selected_str;
        return 1;
    }

    delete selected_str;

    std::string xdg_cmd = "xdg-open " + selected_bookmark->link;
    std::string xdg_err = "Error: Failed to use xdg-open";
    Runner xdg(&xdg_cmd, &xdg_err);
    delete run_cmd(&xdg);

    return 0;
}
