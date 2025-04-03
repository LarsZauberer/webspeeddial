#ifndef config_manager_h_INCLUDED
#define config_manager_h_INCLUDED

#include "webspeeddial/concepts.h"
#include "webspeeddial/config.h"
#include "webspeeddial/utils.h"
namespace core {
    template <typename T, typename N> requires C_ConfigFile<T, N>
    class ConfigManager {
        public:
            ConfigManager(T cf) : cf(cf) {};
            Config &read() {
                if (!cf.exists()) {
                    cfg = get_default_config();
                    write();
                }
                cfg = parse();
                return cfg;
            };
            void set_cfg(Config cfg) {
                this->cfg = cfg;
            }
            void write() {
                std::vector<N*> nodes;
                N root = new N();
                nodes.push_back(root);
                root.set("runner", cfg.runner);
                N bm_nodes = new N();
                nodes.push_back(bm_nodes);
                for (size_t i = 0; i < cfg.bookmarks.size(); i++) {
                    Bookmark& bm = cfg.bookmarks[i];
                    N bm_node = new N();

                    bm_node.set("name", bm.name);
                    bm_node.set("link", bm.link);

                    bm_nodes.set(i, bm_node);
                    nodes.push_back(bm_node);
                }
                root.set("bookmarks", bm_nodes);

                cf.write(root);

                unalloc_all(nodes); 
            }
            Config &get_cfg() {
                return cfg;
            }
        private:
            T cf;
            Config cfg;

            Config get_default_config() {
                Bookmark bm = Bookmark {"Webspeeddial", "github.com/LarsZauberer/webspeeddial"};
                std::vector<Bookmark> bms = {std::move(bm)};
                return Config {
                    "fzf",
                    std::move(bms)
                };
            }

            Config parse() {

            }
    };
}

#endif // config_manager_h_INCLUDED
