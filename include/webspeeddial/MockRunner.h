/**@file MockRunner.h Describes the class MockRunner
 */

#ifndef MockRunner_h_INCLUDED
#define MockRunner_h_INCLUDED

#include <cstdio>
#include <string>
/**@brief A class to test the CMD_Runner capabilities
 */

class MockRunner {
    public:
        /**@brief Creates a MockRunner with some given data
         * The MockRunner will simulate a program that outputs the given data
         * @param data A pointer to a string with the contained data
         */

        MockRunner(std::string *data);

        /**@brief It will return the mock file descriptor
         * @note This file descriptor has to be closed with `this->close()`
         */

        FILE* run();

        /**@brief Ends the `MockRunner`
         * It will close the file descriptor created by the MockRunner
         * This is not a destructor to enable a reuse of the same MockRunner instance.
         */

        void close();
    private:
        FILE* f;
        std::string *mock_data;
};

#endif // MockRunner_h_INCLUDED
