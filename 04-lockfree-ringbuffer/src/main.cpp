#include <iostream>
#include "ring_buffer.hpp"

char *printBool(bool input)
{
    if (input)
    {
        return "Yes";
    }
    else
    {
        return "No";
    }
}

int main()
{
    RingBuffer<int> buffer(5); // Create a buffer of capacity 5

    std::cout << "Initial state:\n";
    std::cout << "empty: " << printBool(buffer.empty()) << ", full: " << buffer.full() << ", size: " << buffer.size() << "\n\n";

    std::cout << "Putting elements: 1 2 3\n";
    buffer.put(1);
    buffer.put(2);
    buffer.put(3);

    std::cout << "After 3 puts:\n";
    std::cout << "empty: " << buffer.empty() << ", full: " << buffer.full() << ", size: " << buffer.size() << "\n\n";

    std::cout << "Getting elements:\n";
    std::cout << buffer.get() << "\n";
    std::cout << buffer.get() << "\n";

    std::cout << "After 2 gets:\n";
    std::cout << "empty: " << buffer.empty() << ", full: " << buffer.full() << ", size: " << buffer.size() << "\n\n";

    std::cout << "Putting elements: 4 5 6 7\n";
    buffer.put(4);
    buffer.put(5);
    buffer.put(6);
    buffer.put(7); // This should make buffer full

    std::cout << "After filling buffer:\n";
    std::cout << "empty: " << buffer.empty() << ", full: " << buffer.full() << ", size: " << buffer.size() << "\n\n";

    std::cout << "Putting 8 (will overwrite oldest):\n";
    buffer.put(8);

    std::cout << "After overwrite:\n";
    std::cout << "empty: " << buffer.empty() << ", full: " << buffer.full() << ", size: " << buffer.size() << "\n";

    std::cout << "Getting all elements:\n";
    while (!buffer.empty())
    {
        std::cout << buffer.get() << " ";
    }
    std::cout << "\n\n";

    std::cout << "After draining:\n";
    std::cout << "empty: " << buffer.empty() << ", full: " << buffer.full() << ", size: " << buffer.size() << "\n\n";

    std::cout << "Resetting buffer\n";
    buffer.reset();
    std::cout << "After reset:\n";
    std::cout << "empty: " << buffer.empty() << ", full: " << buffer.full() << ", size: " << buffer.size() << "\n";

    return 0;
}
