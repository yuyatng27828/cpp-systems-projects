#include <unistd.h>
#include <cstddef>
#include "malloc.hpp"

static Block *freeList = nullptr;

void *naive_malloc(size_t size)
{
    Block *curr = freeList;
    Block *prev = nullptr;

    while (curr)
    {
        if (curr->free && curr->size >= size)
        {
            curr->free = false;
            return (void *)(curr + 1);
        }
        prev = curr;
        curr = curr->next;
    }

    void *mem = sbrk(size + BLOCK_SIZE);
    if (mem == (void *)-1)
    {
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

void naive_free(void *ptr)
{
    if (!ptr)
    {
        return;
    }

    Block *block = (Block *)ptr - 1;
    block->free = true;
}

Block *get_free_list()
{
    return freeList;
}