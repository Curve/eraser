#pragma once

#include <cstddef>
#include <algorithm>

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
