/**@file Runner.h Describes a `CMD_Runner` that runs commands in the terminal
 */

#ifndef Runner_h_INCLUDED
#define Runner_h_INCLUDED

#include "webspeeddial/File.h"

namespace core {
/**@brief A class that can execute certain things
 */

class Runner {
public:
    virtual File *run() {return {};};
};

}; // namespace core

#endif // Runner_h_INCLUDED
