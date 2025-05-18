#include <iostream>
#include <numeric>
#include <vector>
#include <chrono>
#include <thread>
#include <atomic>

void array_sum(const std::vector<int> &arr, size_t start, size_t end, int &local_sum)
{
    local_sum = std::accumulate(arr.begin() + start, arr.begin() + end, 0);
}

void print_result(int num_threads, int sum, std::chrono::duration<double> elapsed)
{
    std::cout << "Number of threads: " << num_threads << std::endl;
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
}

int main()
{
    const size_t array_size = 1000000;
    const int num_threads = std::thread::hardware_concurrency();

    std::vector<int> arr(array_size, 1);
    std::atomic<int> result(0);

    size_t chunk_size = array_size / num_threads;
    size_t remainder = array_size % num_threads;

    std::vector<int> local_sums(num_threads, 0);
    std::vector<std::thread> threads;

    auto start = std::chrono::high_resolution_clock::now();

    size_t start_idx = 0;
    for (int i = 0; i < num_threads; i++)
    {
        size_t end_idx = start_idx + chunk_size + (i < remainder ? 1 : 0);
        threads.emplace_back(array_sum, std::cref(arr), start_idx, end_idx, std::ref(local_sums[i]));
        start_idx = end_idx;
    }

    for (auto &th : threads)
    {
        th.join();
    }

    int total_sum = std::accumulate(local_sums.begin(), local_sums.end(), 0);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;

    print_result(num_threads, total_sum, elapsed);

    return 0;
}