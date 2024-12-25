#pragma once

#include <tuple>

namespace eraser
{
    template <typename>
    struct signature;

    template <typename R, typename... Ts>
    struct signature<R(Ts...)>
    {
        using result    = R;
        using arguments = std::tuple<Ts...>;
    };
} // namespace eraser
