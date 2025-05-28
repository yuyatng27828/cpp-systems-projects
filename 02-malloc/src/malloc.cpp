#include <unistd.h>
#include <cstddef>
#include <iostream>
#include "malloc.hpp"

static Block *list = nullptr;
const size_t MIN_PAYLOAD_SIZE = 4;

void *my_malloc(size_t size)
{
    Block *curr = list;
    Block *prev = nullptr;

    while (curr)
    {
        if (curr->free && curr->size >= size)
        {
            // Splitting the block if it's large enough
            if (curr->size - size >= sizeof(Block) + MIN_PAYLOAD_SIZE)
            {
                Block *newBlock = (Block *)((char *)(curr + 1) + size);
                newBlock->size = curr->size - size - sizeof(Block);
                newBlock->free = true;
                newBlock->next = curr->next;
                newBlock->prev = curr;

                if (curr->next)
                {
                    curr->next->prev = newBlock;
                }

                curr->size = size;
                curr->next = newBlock;
            }

            curr->free = false;
            return (void *)(curr + 1);
        }
        prev = curr;
        curr = curr->next;
    }

    void *mem = sbrk(size + BLOCK_SIZE);
    if (mem == (void *)-1)
    {
        std::cerr << "Memory allocation failed\n";
        return nullptr;
    }

    Block *newBlock = (Block *)mem;
    newBlock->size = size;
    newBlock->free = false;
    newBlock->next = nullptr;

    if (prev)
    {
        prev->next = newBlock;
        newBlock->prev = prev;
    }
    else
    {
        list = newBlock;
        newBlock->prev = nullptr;
    }

    return (void *)(newBlock + 1);
}

void my_free(void *ptr)
{
    if (!ptr)
    {
        return;
    }

    Block *block = (Block *)ptr - 1;
    block->free = true;

    // Forward coalescing
    // If the next block is free, merge it with the current block
    Block *next = block->next;
    if (next && next->free)
    {
        block->size += next->size + sizeof(Block);
        block->next = next->next;
        if (next->next)
        {
            next->next->prev = block;
        }
    }

    // Backward coalescing
    // If the previous block is free, merge it with the current block
    Block *prev = block->prev;
    if (prev && prev->free)
    {
        prev->size += block->size + sizeof(Block);
        prev->next = block->next;
        if (block->next)
        {
            block->next->prev = prev;
        }
    }
}

Block *get_list()
{
    return list;
}