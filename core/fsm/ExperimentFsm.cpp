#include "ExperimentFsm.h"
#include "FsmBridge.h"
#include "EventBus.h"
#include "events.h"
#include "EventBus.h"
#include <QFinalState>

ExperimentFsm::ExperimentFsm(EventBus* bus, QObject* parent) : QObject(parent), bus_(bus) {
    bridge_ = new FsmBridge(bus_, this);
    build();
}



void ExperimentFsm::build()
{
    // 1. 创建状态
    sIdle    = new QState(&m_);
    sReady   = new QState(&m_);
    sImaging = new QState(&m_);
    sPaused  = new QState(&m_);
    sError   = new QState(&m_);
    sFinal   = new QState(&m_); // 先占位

    m_.setInitialState(sIdle);

    // 2. 状态迁移规则 ==================================

    // 2.1 连接成功：Idle -> Ready
    sIdle->addTransition(bridge_, SIGNAL(sigConnected()), sReady);
    sIdle->addTransition(this, SIGNAL(sigConnected()), sReady);//注意注意，这里是为了方便现在再模拟情况下，代替自桥的sigConnected（）信号，后边接了真的要删掉

    // 2.2 Start：Ready --(requestScanStart)--> Imaging
    sReady->addTransition(this, SIGNAL(requestScanStart()), sImaging);

    // 2.3 Pause：Imaging --(requestScanPause)--> Paused
    sImaging->addTransition(this, SIGNAL(requestScanPause()), sPaused);

    // 2.4 Continue：Paused --(requestScanResume)--> Imaging
    sPaused->addTransition(this, SIGNAL(requestScanResume()), sImaging);

    // 2.5 Stop：Imaging/Paused --(requestScanStop)--> Ready
    sImaging->addTransition(this, SIGNAL(requestScanStop()), sReady);
    sPaused ->addTransition(this, SIGNAL(requestScanStop()), sReady);
    sImaging->addTransition(bridge_, SIGNAL(sigScanDone()), sReady);//后续如果接到桥的信号，完成扫描转到SIdle

    // 2.6 Reset：Imaging/Paused/Ready/Error --(requestReset)--> Idle
    sImaging->addTransition(this, SIGNAL(requestReset()), sIdle);
    sPaused ->addTransition(this, SIGNAL(requestReset()), sIdle);
    sReady  ->addTransition(this, SIGNAL(requestReset()), sIdle);
    sError  ->addTransition(this, SIGNAL(requestReset()), sIdle);


    // 2.7 全局错误：任何工作态 -> Error（沿用你原来的 sigError）
    for (QState* st : {sIdle, sReady, sImaging, sPaused}) {
        st->addTransition(bridge_, SIGNAL(sigError(QString)), sError);
    }

    // 如果还想用设备发来的 sigReset 把 Error 拉到 Final，再回 Idle，可以保留：
    sError->addTransition(bridge_, SIGNAL(sigReset()), sFinal);
    sFinal->addTransition(sIdle);

    // 3. 在 状态内entry/exit 里发命令 ==================================

    // 3.1 进入 Imaging：条件选择，开始或继续扫描
    connect(sImaging, &QState::entered, this, [this]{
        if (resumeRequested_) {
            qDebug() << "[FSM] enter Imaging: RESUME -> cmd/scan/resume";

            bus_->publish(Events::kCmdScanResume,
                          Events::makeEnvelope(Events::kCmdScanResume, {}));

            resumeRequested_ = false; // 用完清零

        }
        else
        {
            qDebug() << "[FSM] enter Imaging: START -> cmd/scan/start";

            QVariantMap payload;
            payload.insert("mode", "SPM");
            bus_->publish(Events::kCmdScanStart,
                          Events::makeEnvelope(Events::kCmdScanStart, payload));
        }
        //增加的流水灯测试，后续应该删
        QVariantMap u; u.insert("text", "LED START");
        bus_->publish(Events::kCmdUartSend, Events::makeEnvelope(Events::kCmdUartSend, u));

    });

    // 3.1 退出 Imaging：
    connect(sImaging, &QState::exited, this, [this]{
        QVariantMap u; u.insert("text", "LED STOP");
        bus_->publish(Events::kCmdUartSend, Events::makeEnvelope(Events::kCmdUartSend, u));
    });




    // 3.2 进入 Paused：通知设备暂停
    connect(sPaused, &QState::entered, this, [this]{
        qDebug() << "[FSM] enter Paused: publish cmd/scan/pause";

        bus_->publish(Events::kCmdScanPause,
                      Events::makeEnvelope(Events::kCmdScanPause, {}));
    });

    // 3.3 Ready / Idle：可以统一在进入 Ready/Idle 时发 stop/reset

    // 进入 Ready：停止扫描，但不做全局 reset
    connect(sReady, &QState::entered, this, [this]{
        qDebug() << "[FSM] enter Ready: publish cmd/scan/stop";

        bus_->publish(Events::kCmdScanStop,
                      Events::makeEnvelope(Events::kCmdScanStop, {}));
    });

    // 进入 Idle：做一次全系统 reset（包括清 UI、重置内部状态）
    connect(sIdle, &QState::entered, this, [this]{
        qDebug() << "[FSM] enter Idle: publish sys/reset";

        bus_->publish(Events::kSysReset,
                      Events::makeEnvelope(Events::kSysReset, {}));
    });

    // 3.4 Error：可以记录日志、点亮 UI 提示灯
    connect(sError, &QState::entered, this, [this]{
        qDebug() << "[FSM] enter Error";
        // 可以考虑发一个 sys/error 事件，带上错误信息
    });

    m_.start();
}


void ExperimentFsm::userStart()
{
    qDebug() << "[FSM] userStart()";

    resumeRequested_ = false;//保证image没有start或者continue

    emit sigConnected();//同，为了方便现在模拟情况下，代替自桥的sigConnected（）信号，后边接了真的要删掉
    emit requestScanStart();

}

void ExperimentFsm::userContinue()
{
    qDebug() << "[FSM] userContinue()";

    resumeRequested_ = true;//continue判断信号

    emit requestScanResume();
}

void ExperimentFsm::userPause()
{
    qDebug() << "[FSM] userPause()";
    emit requestScanPause();
}

void ExperimentFsm::userStop()
{
    qDebug() << "[FSM] userStop()";
    emit requestScanStop();
}
void ExperimentFsm::userReset()
{
    qDebug() << "[FSM] userReset()";
    emit requestReset();
}

