// --- External Includes ---
#include "boost/core/noinit_adaptor.hpp"
#include "benchmark/benchmark.h"

// --- STL Includes ---
#include <vector>
#include <cmath>


constexpr const std::size_t arraySize = 1e6;


inline double process(double index)
{
    return std::sqrt(index);
}


template<class TArray>
void growAndInitialize(benchmark::State& r_state)
{
    for (auto dummy : r_state)
    {
        TArray array;
        for (std::size_t i=0; i<arraySize; ++i)
            array.push_back(process(i));
        benchmark::DoNotOptimize(array);
    }
} // void resizeAndInitialize


template<class TArray>
void resizeAndInitialize(benchmark::State& r_state)
{
    for (auto dummy : r_state)
    {
        TArray array(arraySize);
        for (std::size_t i=0; i<arraySize; ++i)
            array[i] = process(i);
        benchmark::DoNotOptimize(array);
    }
} // void resizeAndInitialize


template <class TArray>
void reserveAndInitialize(benchmark::State& r_state)
{
    for (auto dummy : r_state)
    {
        TArray array;
        array.reserve(arraySize);
        for (std::size_t i=0; i<arraySize; ++i)
            array.push_back(process(i));
        benchmark::DoNotOptimize(array);
    }
} // void reserveAndInitialize


template<typename T>
using NoInitVector = std::vector<T,boost::noinit_adaptor<std::allocator<T>>>;


BENCHMARK_TEMPLATE(growAndInitialize, std::vector<double>);
BENCHMARK_TEMPLATE(resizeAndInitialize, std::vector<double>);
BENCHMARK_TEMPLATE(reserveAndInitialize, std::vector<double>);
BENCHMARK_TEMPLATE(growAndInitialize, NoInitVector<double>);
BENCHMARK_TEMPLATE(resizeAndInitialize, NoInitVector<double>);
BENCHMARK_TEMPLATE(reserveAndInitialize, NoInitVector<double>);

BENCHMARK_MAIN();
