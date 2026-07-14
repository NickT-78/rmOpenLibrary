add_library(rmol_domain STATIC
    SettingsController.cpp
)
target_include_directories(rmol_domain PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(rmol_domain PUBLIC Qt6::Core)
set_target_properties(rmol_domain PROPERTIES AUTOMOC ON)
