cmake_minimum_required(VERSION 3.14)
project(foundation CXX)

add_executable(foundation-tests heaps/tests.cpp sorting/tests.cpp)
target_include_directories(foundation-tests PRIVATE ${CMAKE_SOURCE_DIR})
target_compile_options(foundation-tests PRIVATE -std=c++20)

add_executable(foundation-benchmarks sorting/benchmarks.cpp)
target_include_directories(foundation-benchmarks PRIVATE ${CMAKE_SOURCE_DIR})
target_compile_options(foundation-benchmarks PRIVATE -std=c++20)


find_package(fmt CONFIG REQUIRED)
target_link_libraries(foundation-tests PRIVATE fmt::fmt)
target_link_libraries(foundation-benchmarks PRIVATE fmt::fmt)

find_package(GTest CONFIG REQUIRED) 
target_link_libraries(foundation-tests PRIVATE GTest::gtest_main)

find_package(benchmark CONFIG REQUIRED)
target_link_libraries(foundation-benchmarks PRIVATE benchmark::benchmark_main)