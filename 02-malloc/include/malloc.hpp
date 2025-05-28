#ifndef MALLOC_HPP
#define MALLOC_HPP

#include <cstddef>

struct Block
{
    size_t size;
    bool free;
    Block *next;
    Block *prev;
};

const size_t BLOCK_SIZE = sizeof(Block);

void *my_malloc(size_t size);
void my_free(void *ptr);
Block *get_list();

#endif // MALLOC_HPP