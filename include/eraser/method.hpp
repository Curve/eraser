#pragma once

#include "signature.hpp"

#include <type_traits>
#include <concepts>

namespace eraser
{
    namespace impl
    {
        template <typename T>
        struct is_signature : std::false_type
        {
        };

        template <typename T>
        struct is_signature<signature<T>> : std::true_type
        {
        };

        template <typename T>
        concept signature = is_signature<T>::value && std::constructible_from<T>;
    } // namespace impl

    template <auto Name, auto Func, impl::signature Signature>
    struct method
    {
        static constexpr auto name = Name;
        static constexpr auto func = Func;

      public:
        using signature = Signature;
    };
} // namespace eraser
