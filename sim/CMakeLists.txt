add_library(sim STATIC
    ScannerSim.cpp
    ScannerSim.h
)
target_include_directories(sim PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(sim PUBLIC Qt6::Widgets core)
