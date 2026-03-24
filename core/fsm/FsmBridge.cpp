#include "FsmBridge.h"
#include "events.h"
#include "EventBus.h"

FsmBridge::FsmBridge(EventBus* bus, QObject* parent)
    : QObject(parent), bus_(bus)
{
    subscribe();
}

void FsmBridge::subscribe() {
    Q_ASSERT(bus_);

    // 订阅总线：用 QueuedConnection，确保回到 FsmBridge 所在线程
    QObject::connect(bus_, &EventBus::eventPublished, this,
                     [this](const QString& topic, const QVariant& payload) {
                         if (topic == Events::kScanProgress) {
                             const int pct = payload.toMap().value("pct").toInt();
                             emit sigScanProgress(pct);
                         } else if (topic == Events::kScanDone) {
                             emit sigScanDone();
                         } else if (topic == Events::kSysError) {
                             const QString msg = payload.toMap().value("msg").toString();
                             emit sigError(msg);
                         }
                     },
                     Qt::QueuedConnection);
}
