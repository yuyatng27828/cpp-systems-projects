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
    std::lock_guard<std::mutex> lock(mutex_);

    if (empty())
    {
        throw std::runtime_error("Attempted to read from empty buffer");
    }

    T val = buf_[tail_];
    advance_tail();
    full_ = false;

    return val;
}

template <class T>
void RingBuffer<T>::reset()
{
    std::lock_guard<std::mutex> lock(mutex_);
    head_ = 0;
    tail_ = 0;
    full_ = false;
}

template <class T>
bool RingBuffer<T>::empty() const
{
    return (!full_ && (head_ == tail_));
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
    std::lock_guard<std::mutex> lock(mutex_);

    if (full_)
    {
        return max_size_;
    }

    if (head_ >= tail_)
    {
        return head_ - tail_;
    }
    else
    {
        return max_size_ - tail_ + head_;
    }
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