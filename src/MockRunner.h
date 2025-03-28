/**@file MockRunner.h Describes the class MockRunner
 */

#ifndef MockRunner_h_INCLUDED
#define MockRunner_h_INCLUDED

#include <cstdio>
#include <string>
class MockRunner {
    public:
        MockRunner(std::string *data);
        FILE* run();
        void close();
    private:
        FILE* f;
        std::string *mock_data;
};

#endif // MockRunner_h_INCLUDED
