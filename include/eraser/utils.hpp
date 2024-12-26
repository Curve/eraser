#pragma once

#include <tuple>
#include <type_traits>

namespace eraser::utils
{
    template <auto I>
    using constant = std::integral_constant<decltype(I), I>;

    template <typename T>
    using identity = std::type_identity<T>;

    template <typename... Ts>
    using identities = std::type_identity<std::tuple<Ts...>>;
} // namespace eraser::utils
