#pragma once

#include <QObject>
#include <QStateMachine>
#include <QState>

class EventBus;
class FsmBridge;


class ExperimentFsm : public QObject {
    Q_OBJECT
public:
    explicit ExperimentFsm(EventBus* bus, QObject* parent = nullptr);

    // 如需调试可以拿到状态机指针
    QStateMachine* machine() { return &m_; }

public slots:

    void userStart();     // Start 按钮：Ready -> Imaging
    void userPause();     // Pause 按钮：Imaging -> Paused
    void userContinue();  // Continue 按钮：Paused -> Imaging
    void userStop();      // Stop 按钮：Imaging/Paused -> Ready
    void userReset(); // 用户按下 Reset：无条件复位到 Idle

signals:


    void requestScanStart();    // Ready   --(Start)--> Imaging
    void requestScanPause();    // Imaging --(Pause)--> Paused
    void requestScanResume();   // Paused  --(Cont) --> Imaging
    void requestScanStop();     // Imaging/Paused --(Stop)--> Ready
    void requestReset();        // Imaging/Paused/Error/Ready --(Reset)--> Idle
    void sigConnected();       //注意注意，这里是为了方便现在再模拟情况下，代替自桥的sigConnected（）信号，后边接了真的要删掉

private:
    void build();              // 构建状态机图（状态 + 迁移 + entry/exit）

    QStateMachine m_;

    // 各个逻辑状态
    QState *sIdle   {};
    QState *sReady  {};
    QState *sImaging{};
    QState *sPaused {};
    QState *sError  {};
    QState *sFinal  {};  // 如果将来真需要“结束态”，也可以换成 QFinalState


    bool resumeRequested_ = false;//判断是continue还是start用


    EventBus*  bus_    {};   // 用来发布 cmd/scan/...、sys/error 等事件
    FsmBridge* bridge_ {};   // 订阅进度/错误事件，桥接回状态机
};
