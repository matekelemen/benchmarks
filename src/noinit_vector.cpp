// --- External Includes ---
#include "boost/core/noinit_adaptor.hpp"
#include "benchmark/benchmark.h"

// --- STL Includes ---
#include <vector>
#include <cmath>


constexpr const std::size_t arraySize = 1e6;


template <class T>
class Wrapper
{
public:
    Wrapper() noexcept {};
    Wrapper(T value) noexcept : _value(value) {}
    Wrapper(Wrapper&& r_rhs) noexcept = default;
    Wrapper(const Wrapper& r_rhs) noexcept = default;
    Wrapper& operator=(T r_rhs) noexcept {_value = r_rhs; return *this;}
    Wrapper& operator=(Wrapper&& r_rhs) noexcept = default;
    Wrapper& operator=(const Wrapper& r_rhs) noexcept = default;

    operator T() const {return _value;}
    operator T&() {return _value;}

private:
    T _value;
}; // struct Wrapper


template <class T>
inline T process(T index)
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


// --- Standard vector of standard built-ins ---
BENCHMARK_TEMPLATE(growAndInitialize, std::vector<double>)->Name("Standard vector of built-ins: grow");
BENCHMARK_TEMPLATE(resizeAndInitialize, std::vector<double>)->Name("Standard vector of built-ins: resize");
BENCHMARK_TEMPLATE(reserveAndInitialize, std::vector<double>)->Name("Standard vector of built-ins: reserve");

// --- No-init vector of standard built-ins ---
BENCHMARK_TEMPLATE(growAndInitialize, NoInitVector<Wrapper<double>>)->Name("No-init vector of built-ins: grow");
BENCHMARK_TEMPLATE(resizeAndInitialize, NoInitVector<Wrapper<double>>)->Name("No-init vector of built-ins: resize");
BENCHMARK_TEMPLATE(reserveAndInitialize, NoInitVector<Wrapper<double>>)->Name("No-init vector of built-ins: reserve");

// --- Standard vector of wrapped built-ins ---
BENCHMARK_TEMPLATE(growAndInitialize, std::vector<Wrapper<double>>)->Name("Standard vector of wrapped built-ins: grow");
BENCHMARK_TEMPLATE(resizeAndInitialize, std::vector<Wrapper<double>>)->Name("Standard vector of wrapped built-ins: resize");
BENCHMARK_TEMPLATE(reserveAndInitialize, std::vector<Wrapper<double>>)->Name("Standard vector of wrapped built-ins: reserve");

// --- No-init vector of wrapped built-ins ---
BENCHMARK_TEMPLATE(growAndInitialize, NoInitVector<Wrapper<double>>)->Name("No-init vector of wrapped built-ins: grow");
BENCHMARK_TEMPLATE(resizeAndInitialize, NoInitVector<Wrapper<double>>)->Name("No-init vector of wrapped built-ins: resize");
BENCHMARK_TEMPLATE(reserveAndInitialize, NoInitVector<Wrapper<double>>)->Name("No-init vector of wrapped built-ins: reserve");

BENCHMARK_MAIN();
