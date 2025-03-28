/**@file Runner.h Describes a `CMD_Runner` that runs commands in the terminal
 */

#ifndef Runner_h_INCLUDED
#define Runner_h_INCLUDED

#include <string>
class Runner {
    public:
        Runner(std::string *cmd, std::string *err = NULL) : cmd(cmd), err(err) {};
        FILE* run();
        void close();
    private:
        std::string *cmd;
        std::string *err;
        FILE* f;
};

#endif // Runner_h_INCLUDED
