#include <unistd.h>
#include <cstddef>
#include <iostream>
#include "malloc.hpp"

static Block *freeList = nullptr;
const size_t MIN_PAYLOAD_SIZE = 4;

void *my_malloc(size_t size)
{
    Block *curr = freeList;
    Block *prev = nullptr;

    while (curr)
    {
        if (curr->free && curr->size >= size)
        {
            if (curr->size - size >= sizeof(Block) + MIN_PAYLOAD_SIZE)
            {
                Block *newBlock = (Block *)((char *)(curr + 1) + size);
                newBlock->size = curr->size - size - sizeof(Block);
                newBlock->free = true;
                newBlock->next = curr->next;

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
    }
    else
    {
        freeList = newBlock;
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

    Block *next = block->next;
    if (next && next->free)
    {
        block->size += next->size + sizeof(Block);
        block->next = next->next;
    }
}

Block *get_free_list()
{
    return freeList;
}