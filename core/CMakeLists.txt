
add_library(core STATIC
    EventBus.cpp        EventBus.h
    logger.cpp          logger.h
    recorder.cpp        recorder.h
    config.cpp          config.h
    events.h
    fsm/FsmBridge.cpp   fsm/FsmBridge.h
    fsm/ExperimentFsm.cpp fsm/ExperimentFsm.h
)

# QObject 派生类需要 AUTOMOC
set_target_properties(core PROPERTIES AUTOMOC ON)

# 公开本目录，便于 app 引用头文件
target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)


target_link_libraries(core PUBLIC
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::StateMachine
)



