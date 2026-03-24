#pragma once
#include <QObject>
#include <QString>
#include <QVariant>

class EventBus; // 轻量事件总线

class FsmBridge : public QObject {
    Q_OBJECT
public:
    explicit FsmBridge(EventBus* bus, QObject* parent = nullptr);

signals:
    // 提供给 QStateMachine 的触发信号
    void sigConnected();
    void sigScanStarted();
    void sigScanProgress(int pct);
    void sigScanDone();
    void sigError(const QString& msg);
    void sigReset();

private:
    void subscribe();
    EventBus* bus_{nullptr};
};
