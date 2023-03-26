// ------------------------------------------------------
//  John Alexander Ferguson, 2023
//  Distributed under CC0 1.0 Universal licence
// ------------------------------------------------------

#include "libfoundation/sorting/sorting.hpp"

#include <numeric>

#include <benchmark/benchmark.h>

static void BM_insertionSortBest(benchmark::State& state)
{
    std::vector<int> data(state.range());
    std::iota(data.begin(), data.end(), 0);

    for (auto _ : state)
    {
        foundation::sorting::insertionSort(data.begin(), data.end());
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_insertionSortBest)
    ->RangeMultiplier(2)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oN);

static void BM_insertionSortAverage(benchmark::State& state)
{
    std::vector<int> data(state.range());
    std::generate(data.begin(), data.end(), std::rand);

    for (auto _ : state)
    {
        foundation::sorting::insertionSort(data.begin(), data.end());
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_insertionSortAverage)
    ->RangeMultiplier(2)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oN);

static void BM_insertionSortWorst(benchmark::State& state)
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
BENCHMARK(BM_insertionSortWorst)
    ->RangeMultiplier(2)
    ->Range(1 << 5, 1 << 15)
    ->Complexity(benchmark::oN);
