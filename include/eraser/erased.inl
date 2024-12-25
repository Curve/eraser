#pragma once

#include "erased.hpp"

#include <array>
#include <memory>

namespace eraser
{
    namespace impl
    {
        template <typename T>
        struct unique_storage : std::unique_ptr<T>
        {
            template <typename... Ts>
                requires std::constructible_from<T, Ts...>
            unique_storage(Ts &&...args) : std::unique_ptr<T>(std::make_unique<T>(std::forward<Ts>(args)...))
            {
            }

          private:
            using std::unique_ptr<T>::unique_ptr;
        };

        template <typename Interface>
        using vtable = std::array<void *, Interface::size>;

        template <typename Interface, typename T>
        constexpr auto make_vtable()
        {
            vtable<Interface> rtn;

            auto make = [&]<class M, class R, class... Ts>(std::type_identity<std::tuple<M, R, std::tuple<Ts...>>>)
            {
                return +[](void *value, Ts... args) -> R
                {
                    return M::func(*reinterpret_cast<T *>(value), std::forward<Ts>(args)...);
                };
            };

            auto unpack = [&]<std::size_t I>(std::integral_constant<std::size_t, I>)
            {
                using current   = Interface::template at<I>;
                using signature = current::signature;

                using result    = signature::result;
                using arguments = signature::arguments;

                return reinterpret_cast<void *>(make(std::type_identity<std::tuple<current, result, arguments>>{}));
            };

            [&]<std::size_t... Is>(std::index_sequence<Is...>)
            {
                ((rtn[Is] = unpack(std::integral_constant<std::size_t, Is>{})), ...);
            }(std::make_index_sequence<Interface::size>());

            return rtn;
        }
    } // namespace impl

    template <impl::interface Interface, template <typename> typename Storage>
    struct erased<Interface, Storage>::base
    {
        template <typename T>
        struct model;

      public:
        void *value;
        const std::array<void *, Interface::size> *vtable;
    };

    template <impl::interface Interface, template <typename> typename Storage>
    template <typename T>
    class erased<Interface, Storage>::base::model : public base
    {
        static const inline auto vtable = impl::make_vtable<Interface, T>();

      private:
        T m_value;

      public:
        template <typename... Ts>
            requires std::constructible_from<T, Ts...>
        model(Ts &&...args) : base{std::addressof(m_value), std::addressof(vtable)}, m_value{std::forward<Ts>(args)...}
        {
        }
    };

    template <impl::interface Interface, template <typename> typename Storage>
    template <impl::except<erased<Interface, Storage>> T>
    erased<Interface, Storage>::erased(T &&value)
        : m_value(Storage<typename base::template model<T>>{std::forward<T>(value)})
    {
    }

    template <impl::interface Interface, template <typename> typename Storage>
    template <typename T, typename... Ts>
    erased<Interface, Storage>::erased(std::in_place_type_t<T>, Ts &&...args)
        : m_value{Storage<typename base::template model<T>>{std::forward<Ts>(args)...}}
    {
    }

    template <impl::interface Interface, template <typename> typename Storage>
    template <auto Name, typename... Ts>
    auto erased<Interface, Storage>::invoke(Ts &&...args) const
    {
        using method    = Interface::template method<Name>;
        using signature = method::signature;

        using arguments = signature::arguments;
        using result    = signature::result;

        static_assert(std::constructible_from<arguments, Ts...>);

        return [&]<typename... Us>(std::type_identity<std::tuple<Us...>>)
        {
            auto *const func = m_value->vtable->at(Interface::template index<Name>);
            return reinterpret_cast<result (*)(void *, Us...)>(func)(m_value->value, std::forward<Ts>(args)...);
        }(std::type_identity<arguments>{});
    }

    template <typename Interface, typename T, typename... Ts>
    auto make_erased(Ts &&...args)
    {
        return erased<Interface>(std::in_place_type_t<T>{}, std::forward<Ts>(args)...);
    }
} // namespace eraser
