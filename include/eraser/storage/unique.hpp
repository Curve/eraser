#pragma once

#include "../traits/utils.hpp"

#include <memory>

namespace eraser::storage
{
    template <typename T>
    class unique
    {
        std::unique_ptr<T> m_value;

      public:
        template <traits::except<unique<T>> U>
        unique(U &&);

      public:
        T *operator->() const;
    };
} // namespace eraser::storage

#include "unique.inl"
