#ifndef CMD_File_h_INCLUDED
#define CMD_File_h_INCLUDED

#include <cstdio>
namespace core {

/**@brief A wrapper for the FILE
 */

class CMD_File {
    public:
        /**@brief Creates a CMD_File from a file descriptor
         */

        CMD_File(FILE *f) : f(f) {};

        /**@brief Reads a char from a the file descriptor
         * @return It returns char by char from the file descriptor
         */

        char read_c() {return std::fgetc(f);};

        /**@brief Destroys the CMD_File object and with it also the file descriptor
         */

        ~CMD_File() {pclose(f);};
    private:
        FILE *f;
};

};

#endif // CMD_File_h_INCLUDED
