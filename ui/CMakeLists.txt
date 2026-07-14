qt_add_executable(rmOpenLibrary
    main.cpp
    resources.qrc
)
target_link_libraries(rmOpenLibrary PRIVATE
    Qt6::Core Qt6::Quick Qt6::Network
    rmol_domain rmol_data
)
target_include_directories(rmOpenLibrary PRIVATE ${CMAKE_SOURCE_DIR})
