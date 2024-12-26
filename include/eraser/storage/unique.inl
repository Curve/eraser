#pragma once

#include "unique.hpp"

namespace eraser::storage
{
    template <typename T>
    template <traits::except<unique<T>> U>
    unique<T>::unique(U &&value) : m_value{std::make_unique<U>(std::forward<U>(value))}
    {
    }

    template <typename T>
    T *unique<T>::operator->() const
    {
        return m_value.get();
    }
} // namespace eraser::storage
