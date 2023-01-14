#include <benchmark/benchmark.h>
#include "libfoundation/sorting/sorting.hpp"

#include <numeric>

static void BM_insertionSortBest(benchmark::State& state) {

    std::vector<int> data(state.range());
    std::iota(data.begin(), data.end(), 0);    

    for(auto _ : state) {
        Foundation::Sorting::insertionSort(data.begin(), data.end());
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_insertionSortBest)->RangeMultiplier(2)->Range(1<<5, 1<<18)->Complexity(benchmark::oN);

static void BM_insertionSortAverage(benchmark::State& state) {

    std::vector<int> data(state.range());
    std::generate(data.begin(), data.end(), std::rand);    

    for(auto _ : state) {
        Foundation::Sorting::insertionSort(data.begin(), data.end());
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_insertionSortAverage)->RangeMultiplier(2)->Range(1<<5, 1<<18)->Complexity(benchmark::oN);

static void BM_insertionSortWorst(benchmark::State& state) {

    std::vector<int> data(state.range());
    std::iota(data.begin(), data.end(), 0);    
    std::reverse(data.begin(), data.end());

    for(auto _ : state) {
        Foundation::Sorting::insertionSort(data.begin(), data.end());
    }
    state.SetComplexityN(state.range(0));
}
BENCHMARK(BM_insertionSortWorst)->RangeMultiplier(2)->Range(1<<5, 1<<18)->Complexity(benchmark::oN);


