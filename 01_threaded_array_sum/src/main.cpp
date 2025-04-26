#include "array_sum.hpp"
#include <iostream>
#include <vector>
#include <chrono>

int main()
{
    const size_t array_size = 100000000;
    std::vector<int> arr(array_size, 1); // Initialize a large array with 1s
    auto start = std::chrono::high_resolution_clock::now();
    int sum = array_sum(arr);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
    return 0;
}