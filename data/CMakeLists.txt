add_library(rmol_data STATIC
    JsonSettingsStore.cpp
)
target_include_directories(rmol_data PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rmol_data PUBLIC Qt6::Core rmol_domain
    ${SQLITE3_LIBRARY})
target_include_directories(rmol_data PRIVATE ${SQLITE3_INCLUDE_DIR})
set_target_properties(rmol_data PROPERTIES AUTOMOC ON)
