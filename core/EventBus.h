#pragma once
#include <QObject>
#include <QVariant>
#include <functional>

/**
 轻量事件总线：任意线程 emit，订阅端用 Qt::QueuedConnection 接收。
  事件名用字符串，载荷统一用 QVariant。
 */
class EventBus : public QObject {
    Q_OBJECT
public:
    static EventBus& instance() {
        static EventBus bus;
        return bus;
    }
signals:
    void eventPublished(QString topic, QVariant payload); // 线程安全：Qt queued

public:
    void publish(const QString& topic, const QVariant& payload = {}) {
        qDebug() << "[BUS] publish:" << topic << payload;
        emit eventPublished(topic, payload);
    }
    void publish(QStringView topic, const QVariant& payload = {}) {   // 新增

        publish(QString(topic), payload);       //再次传给第一个 publish(const QString& topic, const QVariant& payload = {})
    }

private:
    EventBus() = default;

};



