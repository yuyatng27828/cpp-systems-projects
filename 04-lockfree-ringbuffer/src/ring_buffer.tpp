#pragma once

#include <stdexcept>
#include "ring_buffer.hpp"

template <class T>
RingBuffer<T>::RingBuffer(size_t size)
    : buf_(std::unique_ptr<T[]>(new T[size])),
      max_size_(size)
{
}