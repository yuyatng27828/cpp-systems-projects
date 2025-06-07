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
    std::lock_guard<std::mutex> lock(mutex_);

    buf_[head_] = item;
    if (full_)
    {
        advance_tail();
    }
    advance_head();

    full_ = (head_ == tail_);
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
    return full_;
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
    head_ = (head_ + 1) % max_size_;
}

template <class T>
void RingBuffer<T>::advance_tail()
{
    tail_ = (tail_ + 1) % max_size_;
}