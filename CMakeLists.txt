cmake_minimum_required(VERSION 3.14)
project(flexicache LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SRC_FILES src/*.cpp)
add_executable(flexicache ${SRC_FILES})
