#pragma once

#include "interface.hpp"

#include <concepts>

namespace eraser
{
    namespace impl
    {
        template <typename T>
        struct is_interface : std::false_type
        {
        };

        template <method... Methods>
        struct is_interface<interface<Methods...>> : std::true_type
        {
        };

        template <typename T>
        concept interface = is_interface<T>::value;

        template <typename T, typename U>
        concept except = not std::same_as<std::remove_cvref_t<T>, U>;

        template <typename T>
        struct unique_storage;
    } // namespace impl

    template <impl::interface Interface, template <typename> typename Storage = impl::unique_storage>
    struct erased
    {
        struct base;

      private:
        Storage<base> m_value;

      public:
        template <impl::except<erased<Interface, Storage>> T>
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
