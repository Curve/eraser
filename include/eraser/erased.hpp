#pragma once

#include "traits/interface.hpp"
#include "storage/unique.hpp"

#include <utility>

namespace eraser
{
    template <traits::interface Interface, template <typename> typename Storage = storage::unique>
    struct erased
    {
        struct base;

      private:
        Storage<base> m_value;

      public:
        template <traits::except<erased<Interface, Storage>> T>
        explicit erased(T &&);

        template <typename T, typename... Ts>
        explicit erased(std::in_place_type_t<T>, Ts &&...);

      public:
        template <auto Name, typename... Ts>
        auto invoke(Ts &&...) const;
    };

    template <typename Interface, typename T, typename... Ts>
    auto make_erased(Ts &&...);
} // namespace eraser

#include "erased.inl"
