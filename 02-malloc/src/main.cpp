#include <iostream>
#include "malloc.hpp"

void print_list()
{
    Block *curr = get_list();
    std::cout << "Current memory blocks:\n";
    while (curr)
    {
        std::cout << "Block at " << curr
                  << ": value = " << *(int *)(curr + 1)
                  << ", size = " << curr->size
                  << ", free = " << (curr->free ? "true" : "false")
                  << ", prev = " << curr->prev
                  << ", next = " << curr->next << "\n";
        curr = curr->next;
    }
    std::cout << "\n";
}

void print_separator(const std::string &msg)
{
    std::cout << "\n==== " << msg << " ====\n";
    print_list();
}

int main()
{
    std::cout << "Testing custom malloc/free implementation...\n";

    std::cout << "BLOCK SIZE = " << BLOCK_SIZE << "\n";

    // Allocate 3 blocks
    int *a = static_cast<int *>(my_malloc(sizeof(int)));
    *a = 10;
    int *b = static_cast<int *>(my_malloc(sizeof(int)));
    *b = 20;
    int *c = static_cast<int *>(my_malloc(sizeof(int)));
    *c = 30;

    print_separator("After 3 allocations");

    // Free the middle block (b)
    my_free(b);
    print_separator("After freeing B (should not coalesce)");

    // Free block C (adjacent to B)
    my_free(c);
    print_separator("After freeing C (should coalesce B + C → forward)");

    // Free block A (adjacent to B+C block now)
    my_free(a);
    print_separator("After freeing A (should coalesce A + (B+C) → backward)");

    // Allocate a large block that should be split
    int *d = static_cast<int *>(my_malloc(sizeof(int) * 4)); // Request larger size
    *d = 40;
    print_separator("After allocating large block D (should split the free block)");

    // Free D
    my_free(d);
    print_separator("After freeing D (no coalescing expected unless adjacent block exists)");

    std::cout << "\nAll tests complete.\n";
    return 0;
}