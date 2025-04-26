#include "array_sum.hpp"
#include <numeric>
#include <vector>

int array_sum(const std::vector<int> &arr)
{
    return std::accumulate(arr.begin(), arr.end(), 0);
}