#pragma once

#include <memory>
#include <mutex>
#include <cstddef>

template <class T>
class RingBuffer
{
public:
    explicit RingBuffer(size_t size);

    void put(T item); // Add an item to the buffer
    T get();          // Get and remove the oldest item
    void reset();     // Reset the buffer state

    bool empty() const;      // Check if the buffer is empty
    bool full() const;       // Check if the buffer is full
    size_t capacity() const; // Max number of items
    size_t size() const;     // Current number of items

private:
    mutable std::mutex mutex_; // Thread safety
    std::unique_ptr<T[]> buf_; // Buffer storage
    size_t head_ = 0;          // Write index
    size_t tail_ = 0;          // Read index
    const size_t max_size_;    // Fixed buffer capacity
    bool full_ = false;        // Full flag

    void advance_head(); // Move write index
    void advance_tail(); // Move read index
};

#include "../src/ring_buffer.tpp"
