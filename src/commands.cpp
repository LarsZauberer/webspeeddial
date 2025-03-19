#include "config.h"
#include <cstring>
#include <iostream>
#include <cstdarg>
#include <cstdio>

void runner(char* runner, char** data, char* res) {
    // Null checker
    res = (char*) "";
    if (!runner) {
        return;
    }
    if (!data) {
        return;
    }

    // Open the selector
    FILE* pipe(popen("echo 'Hello\nWorld' | fzf", "r"));
    if (!pipe) {
        std::cout << "Error: Couldn't get file descriptor for the command" << std::endl;
        return;
    }

    // Read the 255 characters from the file
    fgets(res, 255, pipe);

    std::cout << "Selected: " << res << std::endl;

    // Return file descriptor
    pclose(pipe);
}

void xdg_open(char* link) {
    if (!link) {
        return;
    }

    std::cout << "Opening: " << link << std::endl;

    char cmd[LINK_SIZE + 15];
    std::strncpy(cmd, "xdg-open ", 15);
    std::strncpy(cmd, link, LINK_SIZE);

    FILE* f = popen(cmd, "r");
    if (!f) {
        std::cout << "Error: XDG-Open failed" << std::endl;
    }
    pclose(f);
}
