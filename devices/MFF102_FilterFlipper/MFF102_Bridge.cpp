#include "MFF102_Bridge.h"
#include "EventBus.h"
#include "events.h"
#include <QThread>

MFF102_Bridge::MFF102_Bridge(QObject* parent) : QObject(parent)
{


    QString e;
    if (!driver_.init(&e)) error("MFF init failed: " + e);
    else log(QString("MFF init ok. simulation=%1").arg(MFF_USE_SIMULATION ? "ON" : "OFF"));



    auto& bus = EventBus::instance();
    connect(&bus, &EventBus::eventPublished, this,
            [this](const QString& topic, const QVariant& payload)
            {
                if (topic == Events::kCmdMffRefresh) {
                    QString e;
                    auto list = driver_.refreshDevices(&e);
                    if (!e.isEmpty()) error("refresh: " + e);
                    EventBus::instance().publish(Events::kEvtMffDevices, list);
                    log(QString("refresh ok, found %1 device(s)").arg(list.size()));
                }
                else if (topic == Events::kCmdMffConnect) {
                    QString serial = payload.toMap().value("serial").toString();
                    QString e;
                    if (driver_.open(serial, &e)) {
                        EventBus::instance().publish(Events::kEvtMffConnected, QVariantMap{{"serial", serial}});
                        log("connected: " + serial);

                        driver_.clearMessageQueue();

                        //home
                        QString eh;
                        if (!driver_.home(&eh)) error("home failed: " + eh);
                        else log("home issued");


                        // 连接后 1秒读一次
                        driver_.startPolling(500);//由于getPosition必须在polling下使用，所以先开启polling

                        QTimer::singleShot(600, this, [this]{
                         if (!driver_.isOpen()) return;

                        //driver_.startPolling(500);//如果放在这里，开始轮询，然后后边几行代码很快运行完然后读取状态，来不及200ms更新缓存

                         QString e1;
                         int pos = driver_.getPosition(&e1);
                         EventBus::instance().publish(Events::kEvtMffPosition,
                                                      QVariantMap{{"serial", driver_.serial()}, {"position", pos}, {"reason", "After-Flip"}});
                         if (!e1.isEmpty()) error("readPosition: " + e1);
                         log(QString("readOnce(%1): pos=%2 ")
                                 .arg("After-Flip").arg(pos));
                         driver_.stopPolling();
                        });

                    } else {
                        error("connect failed: " + e);
                    }
                }


                else if (topic == Events::kCmdMffDisconnect) {

                    driver_.stopPolling();
                    driver_.close();
                    EventBus::instance().publish(Events::kEvtMffDisconnected, {});
                    log("disconnected");
                }
                else if (topic == Events::kCmdMffStartPolling) {
                    int ms = payload.toMap().value("interval_ms", 200).toInt();
                    QString e;
                    if (driver_.startPolling(ms, &e)) {
                        log(QString("polling started: %1 ms").arg(ms));
                    } else error("startPolling failed: " + e);
                }
                else if (topic == Events::kCmdMffStopPolling) {
                    driver_.stopPolling();
                    log("polling stopped");
                }
                else if (topic == Events::kCmdMffFlip) {
                    int pos = payload.toMap().value("pos").toInt();
                    QString e;
                    if (driver_.flipTo(pos, &e)) log(QString("flip to %1").arg(pos));
                    else error("flip failed: " + e);

                    log(QString("flip issued to %1").arg(pos));

                    // 动作后按 transitTime + margin 读一次
                    QString te;
                    int transitMs = driver_.getTransitTime(&te);
                    const int marginMs = 200;             // 边距值
                    const int delayMs  = transitMs + marginMs;


                    driver_.startPolling(200);//由于getPosition必须在polling下使用，所以先开启polling

                    QTimer::singleShot(delayMs, this, [this]{
                        if (!driver_.isOpen()) return;

                        //driver_.startPolling(500);//如果放在这里，开始轮询，然后后边几行代码很快运行完然后读取状态，来不及200ms更新缓存

                        QString e1;
                        int pos = driver_.getPosition(&e1);
                        EventBus::instance().publish(Events::kEvtMffPosition,
                                                     QVariantMap{{"serial", driver_.serial()}, {"position", pos}, {"reason", "After-Flip"}});
                        if (!e1.isEmpty()) error("readPosition: " + e1);
                        log(QString("readOnce(%1): pos=%2 ")
                                .arg("After-Flip").arg(pos));
                        driver_.stopPolling();

                    });
                }
                else if (topic == Events::kCmdMffReadPosition) {
                    QString e;
                    int pos = driver_.getPosition(&e);
                    EventBus::instance().publish(Events::kEvtMffPosition,
                                                 QVariantMap{{"serial", driver_.serial()}, {"position", pos}});
                    if (!e.isEmpty()) error("readPosition: " + e);
                }
/*                else if (topic == Events::kCmdMffReadStatus) {
                    QString e;
                    auto bits = driver_.getStatusBits(&e);
                    EventBus::instance().publish(Events::kEvtMffStatus,
                                                 QVariantMap{{"serial", driver_.serial()}, {"statusBits", (qulonglong)bits}});
                    if (!e.isEmpty()) error("readStatus: " + e);
                }
*/
            }, Qt::QueuedConnection);
}

MFF102_Bridge::~MFF102_Bridge()
{
    driver_.stopPolling();
    driver_.close();
    driver_.shutdown();
}

void MFF102_Bridge::log(const QString& s)
{
    EventBus::instance().publish(Events::kEvtMffLog, QVariantMap{{"text", s}});
}

void MFF102_Bridge::error(const QString& s)
{
    EventBus::instance().publish(Events::kEvtMffError, QVariantMap{{"text", s}});
}

