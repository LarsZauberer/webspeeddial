#ifndef concepts_h_INCLUDED
#define concepts_h_INCLUDED

#include <concepts>
#include <cstddef>
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
        {t.run(cmd, input)} -> std::same_as<F*>;
    };
}

#endif // concepts_h_INCLUDED
