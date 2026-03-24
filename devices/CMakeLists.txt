add_library(devices STATIC
    MFF102_FilterFlipper/MFF102_Bridge.cpp
    MFF102_FilterFlipper/MFF102_Driver.cpp
)

target_include_directories(devices PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/DLL_MFF102_FilterFlipper
)

# 模拟/真实开关：
option(MFF_USE_SIMULATION "Use Kinesis simulator" ON)
if(MFF_USE_SIMULATION)
    target_compile_definitions(devices PUBLIC MFF_USE_SIMULATION=1)
else()
    target_compile_definitions(devices PUBLIC MFF_USE_SIMULATION=0)
endif()

# 链接厂商的  lib
target_link_libraries(devices PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    core
    "${CMAKE_CURRENT_SOURCE_DIR}/DLL_MFF102_FilterFlipper/Thorlabs.MotionControl.FilterFlipper.lib"
)

