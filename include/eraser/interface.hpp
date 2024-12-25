#pragma once

#include "method.hpp"

namespace eraser
{
    namespace impl
    {
        template <typename T>
        struct is_method : std::false_type
        {
        };

        template <auto Func, auto Name, typename Signature>
        struct is_method<method<Func, Name, Signature>> : std::true_type
        {
        };

        template <typename T>
        concept method = is_method<T>::value;
    } // namespace impl

    template <impl::method... Methods>
    struct interface
    {
        using methods              = std::tuple<Methods...>;
        static constexpr auto size = sizeof...(Methods);

      private:
        template <auto Name, auto I = 0>
        static consteval auto find();

      public:
        template <auto Name>
        static constexpr auto index = find<Name>();

        template <auto Index>
        using at = std::tuple_element_t<Index, methods>;

        template <auto Name>
        using method = at<index<Name>>;
    };
} // namespace eraser

#include "interface.inl"
