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

    // Read the 255 characters from the file
    char read[256];
    fgets(read, 255, pipe);

    std::cout << "Selected: " << read << std::endl;

    // Return file descriptor
    pclose(pipe);
    return read;
}

void xdg_open(string* link) {
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
