#pragma once

#include <stdexcept>
#include "ring_buffer.hpp"

template <class T>
RingBuffer<T>::RingBuffer(size_t size)
    : buf_(std::unique_ptr<T[]>(new T[size])),
      max_size_(size)
{
}

template <class T>
void RingBuffer<T>::put(T item)
{
    // TODO: Implement put logic
}

template <class T>
T RingBuffer<T>::get()
{
    // TODO: Implement get logic
    return T();
}

template <class T>
void RingBuffer<T>::reset()
{
    // TODO: Implement reset logic
}

template <class T>
bool RingBuffer<T>::empty() const
{
    // TODO: Implement empty check;
    return false;
}

template <class T>
bool RingBuffer<T>::full() const
{
    // TODO: Implement full check;
    return false;
}

template <class T>
size_t RingBuffer<T>::capacity() const
{
    return max_size_;
}

template <class T>
size_t RingBuffer<T>::size() const
{
    // TODO: Implement size calculation
    return 0;
}

template <class T>
void RingBuffer<T>::advance_head()
{
    // TODO: Implement circulat increment of head
}

template <class T>
void RingBuffer<T>::advance_tail()
{
    // TODO: Implement circular increment of tail
}