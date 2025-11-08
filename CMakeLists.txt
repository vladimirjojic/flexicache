cmake_minimum_required(VERSION 3.14)
project(flexicache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SRC_FILES src/*.cpp)
add_executable(flexicache ${SRC_FILES})

add_subdirectory(external/doctest)
add_executable(flexicache_tests tests/tests.cpp)
target_link_libraries(flexicache_tests PRIVATE doctest)
target_include_directories(flexicache_tests PRIVATE
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/external/doctest)
