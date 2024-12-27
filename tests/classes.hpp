#pragma once

#include <functional>

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
