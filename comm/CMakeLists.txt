add_library(comm STATIC
    SerialBridge.cpp
    SerialBridge.h
)

target_include_directories(comm PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(comm PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::SerialPort
    core
)
