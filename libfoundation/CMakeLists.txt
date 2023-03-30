cmake_minimum_required(VERSION 3.14)
project(foundation CXX)

find_package(fmt CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED) 
find_package(benchmark CONFIG REQUIRED)

#{{{ library: foundation
add_library(foundation STATIC core/io.cpp)
target_include_directories(foundation PUBLIC ${CMAKE_SOURCE_DIR})
set_property(TARGET foundation PROPERTY CXX_STANDARD 20)
target_link_libraries(foundation PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(foundation PUBLIC fmt::fmt)
#}}}
#{{{ executable: foundation-tests
add_executable(foundation-tests heaps/heaps.tests.cpp 
                                sorting/sorting.tests.cpp
                                rbtree/rbtree.tests.cpp)
set_property(TARGET foundation-tests PROPERTY CXX_STANDARD 20)
target_link_libraries(foundation-tests PRIVATE foundation)
target_link_libraries(foundation-tests PRIVATE GTest::gtest_main)
#}}}
#{{{ executable: foundation-benchmarks
add_executable(foundation-benchmarks 
sorting/sorting.benchmarks.cpp)
set_property(TARGET foundation-benchmarks PROPERTY CXX_STANDARD 20)
target_link_libraries(foundation-benchmarks PRIVATE foundation)
target_link_libraries(foundation-benchmarks PRIVATE benchmark::benchmark_main)
#}}}








