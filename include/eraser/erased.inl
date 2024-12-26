#pragma once

#include "erased.hpp"
#include "utils.hpp"

#include <array>

namespace eraser
{
    namespace impl
    {
        template <typename Interface>
        using vtable = std::array<void *, Interface::size>;

        template <typename Interface, typename T>
        auto make_vtable()
        {
            vtable<Interface> rtn;

            auto make = [&]<typename M, typename R, typename... Ts>(utils::identities<M, R, std::tuple<Ts...>>)
            {
                return +[](void *value, Ts... args) -> R
                {
                    return M::func(*reinterpret_cast<T *>(value), std::forward<Ts>(args)...);
                };
            };

            auto unpack = [&]<auto I>(utils::constant<I>)
            {
                using current = Interface::template at<I>;

                using result    = current::result;
                using arguments = current::arguments;

                return reinterpret_cast<void *>(make(utils::identities<current, result, arguments>{}));
            };

            [&]<auto... Is>(std::index_sequence<Is...>)
            {
                ((rtn[Is] = unpack(utils::constant<Is>{})), ...);
            }(std::make_index_sequence<Interface::size>());

            return rtn;
        }
    } // namespace impl

    template <traits::interface Interface, template <typename> typename Storage>
    struct erased<Interface, Storage>::base
    {
        template <typename T>
        struct model;

      public:
        void *value;
        const impl::vtable<Interface> *vtable;
    };

    template <traits::interface Interface, template <typename> typename Storage>
    template <typename T>
    class erased<Interface, Storage>::base::model : public base
    {
        static const inline auto vtable = impl::make_vtable<Interface, T>();

      private:
        T m_value;

      public:
        template <traits::except<model<T>> U>
        model(U &&value) : base{std::addressof(m_value), std::addressof(vtable)}, m_value{std::forward<U>(value)}
        {
        }

        template <typename... Us>
        model(std::in_place_t, Us &&...args)
            : base{std::addressof(m_value), std::addressof(vtable)}, m_value{std::forward<Us>(args)...}
        {
        }
    };

    template <traits::interface Interface, template <typename> typename Storage>
    template <traits::except<erased<Interface, Storage>> T>
    erased<Interface, Storage>::erased(T &&value) : m_value{typename base::template model<T>{std::forward<T>(value)}}
    {
    }

    template <traits::interface Interface, template <typename> typename Storage>
    template <typename T, typename... Ts>
    erased<Interface, Storage>::erased(std::in_place_type_t<T>, Ts &&...args)
        : m_value{typename base::template model<T>{std::in_place_t{}, std::forward<Ts>(args)...}}
    {
    }

    template <traits::interface Interface, template <typename> typename Storage>
    template <auto Name, typename... Ts>
    auto erased<Interface, Storage>::invoke(Ts &&...args) const
    {
        using method = Interface::template method<Name>;

        using result    = method::result;
        using arguments = method::arguments;

        static_assert(std::constructible_from<arguments, Ts...>);

        return [&]<typename... Us>(utils::identities<Us...>)
        {
            auto *const func = m_value->vtable->at(Interface::template index<Name>);
            return reinterpret_cast<result (*)(void *, Us...)>(func)(m_value->value, std::forward<Ts>(args)...);
        }(utils::identity<arguments>{});
    }

    template <typename Interface, typename T, typename... Ts>
    auto make_erased(Ts &&...args)
    {
        return erased<Interface>(std::in_place_type_t<T>{}, std::forward<Ts>(args)...);
    }
} // namespace eraser
