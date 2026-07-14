cmake_minimum_required(VERSION 3.16)
project(rmOpenLibrary VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build unit/integration tests" ON)

find_package(Qt6 6.8 COMPONENTS Core Quick Network REQUIRED)

# QtSql absent de l'image reMarkable minimale (cf ADR-003) — SqliteCache
# utilise libsqlite3 C API directement, liée manuellement ci-dessous.
find_library(SQLITE3_LIBRARY NAMES sqlite3 REQUIRED)
find_path(SQLITE3_INCLUDE_DIR NAMES sqlite3.h REQUIRED)

add_subdirectory(domain)
add_subdirectory(data)
add_subdirectory(ui)

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
