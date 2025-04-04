#ifndef concepts_h_INCLUDED
#define concepts_h_INCLUDED

#include "webspeeddial/config.h"
#include <concepts>
#include <cstddef>
#include <fstream>
#include <optional>
#include <string>
namespace core {
    /**@brief A concept that describes a Buffer.
     *
     * A buffer has the following properties:
     * 
     * - `t.size()`` which returns a size_t
     * 
     * - `t[i]` which yields a reference to the given datatype D
     * 
     * @tparam D is the Datatype that the buffer should carry
     */

    template <typename T, typename D>
    concept Buffer = requires(T t, size_t i) {
        {t.size()} -> std::same_as<size_t>;
        {t[i]} -> std::same_as<D&>;
    };

    /**@brief A concept that describes a file descriptor given back by a cmd run
     */
    template <typename T>
    concept File = requires(T t) {
        {t.read_c()} -> std::same_as<char>;
    };

    /**@brief A concept that describes a runner that runs cmd commands
     */
    template <typename T, typename F>
    concept Runner = File<F> && requires(T t, std::string &cmd, std::string &input) {
        {t.run(cmd, input)} -> std::same_as<std::optional<F>>;
    };

    /**@brief A concept that describes a parsed node in a config file
     */
     template <typename T>
     concept C_Node = requires(T t, std::string str, size_t i, T *o, std::ofstream stream) {
         {T()};
         {t.get(str)} -> std::same_as<T*>;
         {t.get(i)} -> std::same_as<T*>;
         {t.set(str, o)};
         {t.set(i, o)};
         {t.write(stream)};
         {t.as_string} -> std::same_as<std::string>; 
         {t.is_defined} -> std::same_as<bool>;
         {t.is_sequence} -> std::same_as<bool>;
     };

     /**@brief A concept that describes all the I/O operations for a config file
      */
      template <typename T, typename N>
      concept C_ConfigFile = C_Node<N> && requires(T t, N n) {
          {t.exists()} -> std::same_as<bool>;
          // {t.dir_exists()} -> std::same_as<bool>;
          {t.write(n)};
          {t.read()} -> std::same_as<N*>;
      };

    /**@brief A conecept that describes a manager for the Config
     */
    template <typename T>
    concept C_ConfigManager = requires (T t, Config cfg) {
        {t.read()} -> std::same_as<Config&>;
        {t.set(cfg)};
        {t.write()};
        {t.get_cfg()} -> std::same_as<Config&>;
    };
}

#endif // concepts_h_INCLUDED
