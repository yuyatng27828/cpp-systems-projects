#include <iostream>
#include "malloc.hpp"

int main()
{
    std::cout << "Testing naive_malloc and naive_free...\n";
    std::cout << "BLOCK SIZE = " << BLOCK_SIZE << "\n";

    int *a = static_cast<int *>(my_malloc(sizeof(int)));
    *a = 10;
    std::cout << "Allocating Block A:" << "\n";
    std::cout << "Value=" << *a << "\n";
    std::cout << "Address=" << a << "\n";
    int *b = static_cast<int *>(my_malloc(sizeof(int)));
    *b = 20;
    std::cout << "Allocating Block B:" << "\n";
    std::cout << "Value=" << *b << "\n";
    std::cout << "Address=" << b << "\n";
    int *c = static_cast<int *>(my_malloc(sizeof(int)));
    *c = 30;
    std::cout << "Allocating Block C:" << "\n";
    std::cout << "Value=" << *c << "\n";
    std::cout << "Address=" << c << "\n";
    int *d = static_cast<int *>(my_malloc(sizeof(int)));
    *d = 40;
    std::cout << "Allocating Block D:" << "\n";
    std::cout << "Value=" << *d << "\n";
    std::cout << "Address=" << d << "\n";
    int *e = static_cast<int *>(my_malloc(sizeof(int)));
    *e = 50;
    std::cout << "Allocating Block E:" << "\n";
    std::cout << "Value=" << *e << "\n";
    std::cout << "Address=" << e << "\n";
    int *f = static_cast<int *>(my_malloc(sizeof(int)));
    *f = 60;
    std::cout << "Allocating Block F:" << "\n";
    std::cout << "Value=" << *f << "\n";
    std::cout << "Address=" << f << "\n";

    std::cout << "Freeing Block F...\n";
    my_free(f);
    std::cout << "Freeing Block E...\n";
    my_free(e);
    std::cout << "Freeing Block C...\n";
    my_free(c);
    std::cout << "Freeing Block B...\n";
    my_free(b);

    int *g = static_cast<int *>(my_malloc(sizeof(int)));
    *g = 70;
    std::cout << "Allocating Block G:" << "\n";
    std::cout << "Value=" << *g << "\n";
    std::cout << "Address=" << g << "\n";

    std::cout << "Printing List...\n";
    Block *curr = get_free_list();
    while (curr != nullptr)
    {
        void *payload = (void *)(curr + 1);
        std::cout << "Value=" << *static_cast<int *>(payload)
                  << ", Address=" << payload
                  << ", Free=" << (curr->free ? "Yes" : "No")
                  << ", Size=" << curr->size << "\n";
        curr = curr->next;
    }

    return 0;
}