cmake_minimum_required(VERSION 3.14)
project(foundation CXX)

find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED) 
find_package(benchmark CONFIG REQUIRED)

#{{{ library: foundation
add_library(foundation SHARED core/io.cpp)
target_include_directories(foundation PUBLIC ${CMAKE_SOURCE_DIR})
target_compile_options(foundation PUBLIC -std=c++20)
target_link_libraries(foundation PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(foundation PUBLIC fmt::fmt)
#}}}
#{{{ executable: foundation-tests
add_executable(foundation-tests heaps/heaps.tests.cpp 
                                sorting/sorting.tests.cpp
                                rbtree/rbtree.tests.cpp)
target_link_libraries(foundation-tests PRIVATE foundation)
target_link_libraries(foundation-tests PRIVATE GTest::gtest_main)
#}}}
#{{{ executable: foundation-benchmarks
add_executable(foundation-benchmarks 
sorting/sorting.benchmarks.cpp)
target_link_libraries(foundation-benchmarks PRIVATE foundation)
target_link_libraries(foundation-benchmarks PRIVATE benchmark::benchmark_main)
#}}}








