#pragma once

#include <type_traits>
#include <vector>

template <typename T, typename... Args>
constexpr bool is_any_of_v = std::disjunction_v<std::is_same<T, Args>...>;

template <typename T>
struct is_any_of : std::bool_constant<is_any_of_v<T>> {};
