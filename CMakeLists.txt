cmake_minimum_required(VERSION 3.16)
project(rmOpenLibrary VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build unit/integration tests" ON)

find_package(Qt5 COMPONENTS Core Quick Network Sql REQUIRED)

add_subdirectory(domain)
add_subdirectory(data)
add_subdirectory(ui)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
