#pragma once

#include <assert.h>
#include <string_view>
#include <concepts>

using namespace std::literals::string_view_literals;

// clang-format off
template<typename T>
concept not_null = 
    !std::is_assignable_v<T&, std::nullptr_t> && 
    requires(T t) {
        { *t } -> std::convertible_to<typename std::pointer_traits<T>::element_type&>;
        { t->*t } -> std::convertible_to<typename std::pointer_traits<T>::element_type*>;
    };
// clang-format on