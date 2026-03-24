#include "ScannerSim.h"
#include "EventBus.h"
#include "events.h"

ScannerSim::ScannerSim(QObject* parent) : QObject(parent) {
    timer_.setInterval(50);
    connect(&timer_, &QTimer::timeout, this, &ScannerSim::onTick);
    wireBus();
}

void ScannerSim::wireBus() {
    auto& bus = EventBus::instance();

    // 听命令：开始/停止扫描
    connect(&bus, &EventBus::eventPublished, this,
            [this](const QString& topic, const QVariant&) {
                if (topic == Events::kCmdScanStart) {
                    running_  = true;
                    progress_ = 0;
                    timer_.start();
                } else if (topic == Events::kCmdScanStop) {
                    running_ = false;
                    timer_.stop();
                }
                if (topic == Events::kCmdScanPause) {
                    running_  = false;
                    timer_.stop();
                }
                else if (topic == Events::kCmdScanResume) {
                    if (progress_ < 100) {
                        running_ = true;
                        timer_.start();
                    }
                }


            },
            Qt::QueuedConnection);
}

void ScannerSim::onTick() {
    if (!running_) return;
    progress_ += 1;
    EventBus::instance().publish(Events::kScanProgress, QVariantMap{{"pct", progress_}});
    if (progress_ >= 100) {
        EventBus::instance().publish(Events::kScanDone, QVariantMap{});
        running_ = false; timer_.stop(); progress_ = 0;
    }

}
