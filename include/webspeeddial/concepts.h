#ifndef concepts_h_INCLUDED
#define concepts_h_INCLUDED

#include <concepts>
#include <cstddef>
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
}

#endif // concepts_h_INCLUDED
