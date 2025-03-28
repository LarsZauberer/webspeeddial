#ifndef concepts_h_INCLUDED
#define concepts_h_INCLUDED

#include "config.h"
#include <concepts>
#include <cstddef>
template <typename T, typename D>
concept Indexable = requires(T t, size_t i) {
  { t[i] } -> std::same_as<D &>;
};

template <typename T>
concept Sizable = requires(T t) {
  { t.size() } -> std::convertible_to<size_t>;
};

template <typename T, typename D>
concept Buffer = Indexable<T, D> && Sizable<T>;

/**@brief Concept describing a system that runs a command in the terminal and
 * returns a file descriptor It has to provide the following things
 * - A `run()` command that returns a `FILE*`
 * - A `close()` command (closing the file descriptor)
 */

template <typename T>
concept CMD_Runner = requires(T t, std::string *cmd, std::string *err) {
  { t.run() } -> std::same_as<FILE *>;
  { t.close() };
};

#endif // concepts_h_INCLUDED
