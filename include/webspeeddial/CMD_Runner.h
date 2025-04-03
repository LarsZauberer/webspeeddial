#ifndef CMD_Runner_h_INCLUDED
#define CMD_Runner_h_INCLUDED

#include "webspeeddial/CMD_File.h"
#include <cstdio>
#include <iostream>
#include <optional>
#include <string>
namespace core {
    /**@brief A runner that runs commands on the system
     */
     class CMD_Runner {
        public:
            CMD_Runner() = default;
            CMD_Runner(CMD_Runner &&other) {std::cout << "CMD_Runner moved" << std::endl;};

            CMD_File *run(std::string &cmd, std::string &input) {
                std::string command = "echo '" + input + "' | " + cmd;
                FILE *f = popen(command.data(), "r");
                if (!f) {
                    std::cout << "Error while executing command: " << command << std::endl;
                    return nullptr;
                }
                return new CMD_File(f); 
            }
     };
};

#endif // CMD_Runner_h_INCLUDED
