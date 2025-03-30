#ifndef YamlConfigFile_h_INCLUDED
#define YamlConfigFile_h_INCLUDED

#include "webspeeddial/IConfigFile.h"
#include <filesystem>
namespace core {
    class YamlConfigFile : public IConfigFile {
        public:
        YamlConfigFile();
        YamlConfigFile(std::filesystem::path path);
        ~YamlConfigFile();

        INode* read();
        void write(INode*);
        bool file_exists();
        void create_dirs();

        private:
            INode* main_node;
            std::filesystem::path path;
    };
}

#endif // YamlConfigFile_h_INCLUDED
