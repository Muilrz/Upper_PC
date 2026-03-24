cmake_minimum_required(VERSION 3.19)
project(UpperPC_2_0 LANGUAGES CXX)




set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt  moc/uic/rcc
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 一次性导入所有需要的 Qt 模块
find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets Core StateMachine SerialPort)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Core StateMachine SerialPort)



add_subdirectory(hal)
add_subdirectory(core)
add_subdirectory(sim)
add_subdirectory(comm)
add_subdirectory(devices)
add_subdirectory(app)







