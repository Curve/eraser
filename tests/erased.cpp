#include <boost/ut.hpp>
#include <eraser/erased.hpp>

using namespace boost::ut;
using namespace boost::ut::bdd;

#include "classes.hpp"

enum class methods
{
    a,
    b,
};

template <std::size_t N>
struct str
{
    char buffer[N]{}; // NOLINT

  public:
    constexpr str(const char (&str)[N]) // NOLINT
    {
        std::copy(str, str + N, buffer); // NOLINT
    }

  public:
    constexpr bool operator==(const str &other) const
    {
        return std::equal(buffer, buffer + N, other.buffer); // NOLINT
    }
};

// NOLINTNEXTLINE
suite<"erased"> erased_suite = []()
{
    using eraser::method;
    using eraser::erased;
    using eraser::make_erased;

    int target{};

    {
        using interface = eraser::interface<                                                          //
            method<methods::a, [](auto &self) { return self.a(); }, int()>,                           //
            method<methods::b, [](auto &self, int &target) { return self.b(target); }, double(int &)> //
            >;

        erased<interface> e1 = make_erased<interface, erase_me>(&target);
        erased<interface> e2{erase_me_too{std::ref(target)}};

        expect(eq(e1.invoke<methods::a>(), 10));
        expect(eq(target, 10));

        expect(eq(e2.invoke<methods::a>(), 30));
        expect(eq(target, 30));

        expect(eq(e1.invoke<methods::b>(target), 3.14));
        expect(eq(target, 20));

        expect(eq(e2.invoke<methods::b>(target), 2.71));
        expect(eq(target, 40));
    }

    {
        using interface = eraser::interface<                                                        //
            method<str{"a"}, [](auto &self) { return self.a(); }, int()>,                           //
            method<str{"b"}, [](auto &self, int &target) { return self.b(target); }, double(int &)> //
            >;

        erased<interface> e1 = make_erased<interface, erase_me>(&target);
        erased<interface> e2{erase_me_too{std::ref(target)}};

        expect(eq(e1.invoke<str{"a"}>(), 10));
        expect(eq(target, 10));

        expect(eq(e2.invoke<str{"a"}>(), 30));
        expect(eq(target, 30));

        expect(eq(e1.invoke<str{"b"}>(target), 3.14));
        expect(eq(target, 20));

        expect(eq(e2.invoke<str{"b"}>(target), 2.71));
        expect(eq(target, 40));
    }
};
