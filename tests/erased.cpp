#include <boost/ut.hpp>
#include <eraser/erased.hpp>
#include <eraser/storage/shared.hpp>

using namespace boost::ut;
using namespace boost::ut::bdd;

#include "classes.hpp"

using eraser::erased;
using eraser::make_erased;
using eraser::method;

enum class methods
{
    a,
    b,
};

using interface = eraser::interface<                                                          //
    method<methods::a, [](auto &self) { return self.a(); }, int()>,                           //
    method<methods::b, [](auto &self, int &target) { return self.b(target); }, double(int &)> //
    >;

// NOLINTNEXTLINE
suite<"erased"> erased_suite = []()
{
    int target{};

    auto e1 = make_erased<interface, erase_me, eraser::storage::shared>(&target);
    erased<interface> e2{erase_me_too{std::ref(target)}};

    expect(std::copyable<decltype(e1)>);
    expect(not std::copyable<decltype(e2)>);

    expect(eq(e1.invoke<methods::a>(), 10));
    expect(eq(target, 10));

    expect(eq(e2.invoke<methods::a>(), 30));
    expect(eq(target, 30));

    expect(eq(e1.invoke<methods::b>(target), 3.14));
    expect(eq(target, 20));

    expect(eq(e2.invoke<methods::b>(target), 2.71));
    expect(eq(target, 40));

    auto u1 = e1.as<erase_me>();
    expect(u1.has_value());

    expect(eq(u1.value()->a(), 10));
    expect(eq(target, 10));

    auto u2 = e2.as<erase_me_too>();
    expect(u2.has_value());

    expect(eq(u2.value()->a(), 30));
    expect(eq(target, 30));
};
