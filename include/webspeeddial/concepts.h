#ifndef concepts_h_INCLUDED
#define concepts_h_INCLUDED

#include <concepts>
#include <cstddef>
#include <optional>
#include <string>

namespace core {
/**@brief A Type that can be indexed and returns always the same datatype
 *
 * It has to be indexible with a `size_t`.
 *
 * @tparam T The indexible List ADT
 * @tparam D The datatype carried by the List
 */

template <typename T, typename D>
concept Indexable = requires(T t, size_t i) {
  { t[i] } -> std::same_as<D &>;
};

/**@brief A type that has the function `size` and returns an `size_t`
 *
 * @tparam T The datatype. Thought of as a List ADT
 */

template <typename T>
concept Sizable = requires(T t) {
  { t.size() } -> std::convertible_to<size_t>;
};

/**@brief A Buffer containing multiple elements of the same type
 *
 * A Buffer is
 * - Sizable
 * - Indexable
 *
 * @tparam T The List ADT
 * @tparam D The datatype contained in the List
 */

template <typename T, typename D>
concept Buffer = Indexable<T, D> && Sizable<T>;

template <typename T>
concept ReadableFile = requires(T t) {
    {t.read_c()} -> std::same_as<char>;
};

template <typename T>
concept WriteableFile = requires(T t, std::string s) {
    {t.write(s)};
};

/**@brief Concept describing a system that runs a command in the terminal and
 * returns a file descriptor It has to provide the following things
 *
 * - A `run()` command that returns a `FILE*`
 * - A `close()` command (closing the file descriptor)
 */

template <typename T, typename F>
concept CMD_Runner = ReadableFile<F> && requires(T t, std::string *cmd, std::string *err) {
  { t.run() } -> std::same_as<std::optional<F>>;
};

}; // namespace core

#endif // concepts_h_INCLUDED
