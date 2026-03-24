
qt_add_executable(UpperPC_2_0
    mainWindow.cpp
    mainWindow.h
    mainWindow.ui
    main.cpp
    ${PROJECT_SOURCE_DIR}/sim/ScannerSim.cpp
    ${PROJECT_SOURCE_DIR}/sim/ScannerSim.h

)

target_link_libraries(UpperPC_2_0 PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::StateMachine
    Qt${QT_VERSION_MAJOR}::SerialPort
    core
    sim
    comm
    devices
)

target_include_directories(UpperPC_2_0 PRIVATE
    ${PROJECT_SOURCE_DIR}       # 工程根（包含 core/）
    ${CMAKE_CURRENT_BINARY_DIR} # AUTOUIC 生成的 ui_*.h
    ${PROJECT_SOURCE_DIR}/sim
)

# 安装与部署（windeployqt）安装规则（开发阶段可忽略，打包时生效）
include(GNUInstallDirs)

install(TARGETS UpperPC_2_0
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#MFF102  DLL库复制
add_custom_command(TARGET UpperPC_2_0 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/devices/DLL_MFF102_FilterFlipper/Thorlabs.MotionControl.DeviceManager.dll"
        "$<TARGET_FILE_DIR:UpperPC_2_0>"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/devices/DLL_MFF102_FilterFlipper/Thorlabs.MotionControl.FilterFlipper.dll"
        "$<TARGET_FILE_DIR:UpperPC_2_0>"
)



