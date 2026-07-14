find_package(Qt6 COMPONENTS Test REQUIRED)

add_executable(test_searchquery unit/test_searchquery.cpp)
target_link_libraries(test_searchquery PRIVATE Qt6::Test Qt6::Core rmol_domain)
target_include_directories(test_searchquery PRIVATE ${CMAKE_SOURCE_DIR})
set_target_properties(test_searchquery PROPERTIES AUTOMOC ON)
add_test(NAME test_searchquery COMMAND test_searchquery)

add_executable(test_settingscontroller unit/test_settingscontroller.cpp)
target_link_libraries(test_settingscontroller PRIVATE Qt6::Test Qt6::Core rmol_domain rmol_data)
target_include_directories(test_settingscontroller PRIVATE ${CMAKE_SOURCE_DIR})
set_target_properties(test_settingscontroller PROPERTIES AUTOMOC ON)
add_test(NAME test_settingscontroller COMMAND test_settingscontroller)

# Phase 3: test_offline_fallback (integration/) requires NetworkMonitor +
# OpenLibraryClient real implementations, not yet built.
