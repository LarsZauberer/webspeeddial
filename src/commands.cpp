#include "utils.h"
#include <cstring>
#include <iostream>
#include <cstdarg>
#include <cstdio>

using std::string;

/// This function will never return a null. It will return an empty string if it fails.
string runner(string* runner, string* data) {
    // Null checker
    if (!runner) {
        return "";
    }
    if (!data) {
        return "";
    }

    // Open the selector
    string cmd = "echo '" + *data + "' | " + *runner;
    FILE* pipe(popen(cmd.data(), "r"));
    if (!pipe) {
        std::cout << "Error: Couldn't get file descriptor for the command" << std::endl;
        return "";
    }

    // Read stdout from the file
    std::string out = "";
    out.reserve(128);
    char c;
    while (c != EOF){
        c = fgetc(pipe);
        out += c;
    }
    remove_trailing(&out);

    std::cout << "Selected: " << out << std::endl;

    // Return file descriptor
    pclose(pipe);
    return out;
}

void xdg_open(string* link) {
    // Null Checker
    if (!link) {
        return;
    }

    std::cout << "Opening: " << *link << std::endl;

    string cmd = "xdg-open " + *link;
    FILE* f = popen(cmd.data(), "r");
    if (!f) {
        std::cout << "Error: XDG-Open failed" << std::endl;
    }
    pclose(f);
}
