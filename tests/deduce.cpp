#include <boost/ut.hpp>
#include <eraser/experimental/deduce.hpp>

using namespace boost::ut;
using namespace boost::ut::bdd;

#include "classes.hpp"

struct interface
{
    int a()
    {
        return eraser::experimental::call<int>([](auto &self) { return self.a(); }, this);
    }

    double b(int &target)
    {
        return eraser::experimental::call<double>([](auto &self, int &target) { return self.b(target); }, this, target);
    }
};

using eraser::erased;
using eraser::make_erased;
using eraser::experimental::deduce;

// NOLINTNEXTLINE
suite<"deduce"> deduce_suite = []
{
    int target{};

    auto e1 = make_erased<deduce<interface>, erase_me>(&target);
    erased<deduce<interface>> e2{erase_me_too{std::ref(target)}};

    expect(eq(e1.a(), 10));
    expect(eq(target, 10));

    expect(eq(e2.a(), 30));
    expect(eq(target, 30));

    expect(eq(e1.b(target), 3.14));
    expect(eq(target, 20));

    expect(eq(e2.b(target), 2.71));
    expect(eq(target, 40));
};
