// ------------------------------------------------------
//  John Alexander Ferguson, 2023
//  Distributed under CC0 1.0 Universal licence
// ------------------------------------------------------

#include "libfoundation/sorting/sorting.hpp"

#include <numeric>

#include <benchmark/benchmark.h>


// {{{ collection: insertion sort benchmarks
static void BMinsertionSortBest(benchmark::State& state)
{
    std::vector<int> data(state.range());
    std::iota(data.begin(), data.end(), 0);

    for (auto _ : state)
    {
        foundation::sorting::insertionSort(data.begin(), data.end());
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BMinsertionSortBest)
    ->RangeMultiplier(2)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oAuto);

static void BMinsertionSortAverage(benchmark::State& state)
{
    std::vector<int> data(state.range());
    std::generate(data.begin(), data.end(), std::rand);

    for (auto _ : state)
    {
        foundation::sorting::insertionSort(data.begin(), data.end());
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BMinsertionSortAverage)
    ->RangeMultiplier(2)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oAuto);

static void BMinsertionSortWorst(benchmark::State& state)
{
    std::vector<int> data(state.range());
    std::iota(data.begin(), data.end(), 0);
    std::reverse(data.begin(), data.end());

    for (auto _ : state)
    {
        foundation::sorting::insertionSort(data.begin(), data.end());
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BMinsertionSortWorst)
    ->RangeMultiplier(2)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oAuto);
// }}}
// {{{ collection: heap sort benchmarks
static void BMheapSortBest(benchmark::State& state)
{
    std::vector<int> data(state.range());
    std::iota(data.begin(), data.end(), 0);

    for (auto _ : state)
    {
        foundation::sorting::heapSort(data.begin(), data.end());
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BMheapSortBest)
    ->RangeMultiplier(2)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oAuto);

static void BMheapSortAverage(benchmark::State& state)
{
    std::vector<int> data(state.range());
    std::generate(data.begin(), data.end(), std::rand);

    for (auto _ : state)
    {
        foundation::sorting::heapSort(data.begin(), data.end());
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BMheapSortAverage)
    ->RangeMultiplier(2)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oAuto);

static void BMheapSortWorst(benchmark::State& state)
{
    std::vector<int> data(state.range());
    std::iota(data.begin(), data.end(), 0);
    std::reverse(data.begin(), data.end());

    for (auto _ : state)
    {
        foundation::sorting::heapSort(data.begin(), data.end());
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BMheapSortWorst)
    ->RangeMultiplier(2)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oAuto);
// }}}
// {{{ collection: heap sort benchmarks
static void BMquickSortBest(benchmark::State& state)
{
    std::vector<int> data(state.range());
    std::iota(data.begin(), data.end(), 0);

    for (auto _ : state)
    {
        foundation::sorting::heapSort(data.begin(), data.end());
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BMheapSortBest)
    ->RangeMultiplier(2)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oAuto);

static void BMquickSortAverage(benchmark::State& state)
{
    std::vector<int> data(state.range());
    std::generate(data.begin(), data.end(), std::rand);

    for (auto _ : state)
    {
        foundation::sorting::heapSort(data.begin(), data.end());
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BMheapSortAverage)
    ->RangeMultiplier(2)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oAuto);

static void BMquickSortWorst(benchmark::State& state)
{
    std::vector<int> data(state.range());
    std::iota(data.begin(), data.end(), 0);
    std::reverse(data.begin(), data.end());

    for (auto _ : state)
    {
        foundation::sorting::heapSort(data.begin(), data.end());
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BMheapSortWorst)
    ->RangeMultiplier(2)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oAuto);
// }}}