#include <boost/ut.hpp>
#include <eraser/erased.hpp>

using namespace boost::ut;
using namespace boost::ut::bdd;

enum class methods
{
    a,
    b,
};

struct erase_me
{
    int *target;

  public:
    [[nodiscard]] int a() const
    {
        return (*target = 10);
    }

    static double b(int &target)
    {
        target = 20;
        return 3.14;
    }
};

struct erase_me_too
{
    std::reference_wrapper<int> target;

  public:
    [[nodiscard]] int a() const
    {
        return (target.get() = 30);
    }

    static double b(int &target)
    {
        target = 40;
        return 2.71;
    }
};

using eraser::erased;
using eraser::make_erased;
using eraser::method;

using interface = eraser::interface<                                                          //
    method<methods::a, [](auto &self) { return self.a(); }, int()>,                           //
    method<methods::b, [](auto &self, int &target) { return self.b(target); }, double(int &)> //
    >;

// NOLINTNEXTLINE
suite<"erased"> erased_suite = []()
{
    int target{};

    auto e1 = make_erased<interface, erase_me>(&target);
    erased<interface> e2{erase_me_too{std::ref(target)}};

    expect(eq(e1.invoke<methods::a>(), 10));
    expect(eq(target, 10));

    expect(eq(e2.invoke<methods::a>(), 30));
    expect(eq(target, 30));

    expect(eq(e1.invoke<methods::b>(target), 3.14));
    expect(eq(target, 20));

    expect(eq(e2.invoke<methods::b>(target), 2.71));
    expect(eq(target, 40));
};
