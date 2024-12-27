#pragma once

#include "../erased.hpp"

namespace eraser::experimental
{
    template <typename Interface>
    struct deduce;

    template <typename Result = void, typename Func, typename Interface, typename... Ts>
    auto call(Func &&, Interface *, Ts &&...);
} // namespace eraser::experimental

namespace eraser
{
    template <typename Interface>
    struct erased<experimental::deduce<Interface>>;
} // namespace eraser

#include "deduce.inl"
