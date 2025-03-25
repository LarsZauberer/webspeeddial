#ifndef concepts_h_INCLUDED
#define concepts_h_INCLUDED

#include "config.h"
#include <concepts>
#include <cstddef>
template<typename T, typename D>
concept Indexable = requires(T t, size_t i) {
    {t[i]} -> std::same_as<D&> ;
};

template<typename T>
concept Sizable = requires(T t) {
    {t.size()} -> std::convertible_to<size_t>;
};

template<typename T, typename D>
concept Buffer = Indexable<T, D> && Sizable<T>; 

#endif // concepts_h_INCLUDED
