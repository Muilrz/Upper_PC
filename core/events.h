#pragma once
#include <QString>
#include <QVariant>
#include <QDateTime>
#include <QHash>

#include <QStringView>

namespace Events {
//统一topic
inline constexpr QStringView kScanProgress   = u"scan/progress";
inline constexpr QStringView kScanDone       = u"scan/done";
inline constexpr QStringView kSpecFrame      = u"spec/frame";
inline constexpr QStringView kPotStatus      = u"pot/status";
inline constexpr QStringView kDriftEstimate  = u"drift/estimate";
inline constexpr QStringView kCmdScanStart   = u"cmd/scan/start";
inline constexpr QStringView kCmdScanStop    = u"cmd/scan/stop";
inline constexpr QStringView kCmdScanPause  = u"cmd/scan/pause";
inline constexpr QStringView kCmdScanResume = u"cmd/scan/resume";
inline constexpr QStringView kCmdPotSet      = u"cmd/pot/set";
inline constexpr QStringView kCmdSpecAcq     = u"cmd/spec/acq";
inline constexpr QStringView kSysError = u"sys/error";
inline constexpr QStringView kSysReset = u"sys/reset";
// 串口 / OLED
inline constexpr QStringView kUartRx = u"uart/rx";
inline constexpr QStringView kUartStatus   = u"uart/status";
inline constexpr QStringView kCmdUartOpen  = u"cmd/uart/open";
inline constexpr QStringView kCmdUartClose = u"cmd/uart/close";
inline constexpr QStringView kCmdUartSend  = u"cmd/uart/send";
inline constexpr QStringView kCmdOledPrint = u"cmd/oled/print";

//MFF102

inline constexpr QStringView kCmdMffRefresh      = u"cmd/mff/refresh";
inline constexpr QStringView kCmdMffConnect      = u"cmd/mff/connect";
inline constexpr QStringView kCmdMffDisconnect   = u"cmd/mff/disconnect";
inline constexpr QStringView kCmdMffStartPolling = u"cmd/mff/startPolling";
inline constexpr QStringView kCmdMffStopPolling  = u"cmd/mff/stopPolling";
inline constexpr QStringView kCmdMffFlip         = u"cmd/mff/flip";
inline constexpr QStringView kCmdMffReadPosition = u"cmd/mff/readPosition";
//inline constexpr QStringView kCmdMffReadStatus   = u"cmd/mff/readStatus";

inline constexpr QStringView kEvtMffDevices      = u"evt/mff/devices";
inline constexpr QStringView kEvtMffConnected    = u"evt/mff/connected";
inline constexpr QStringView kEvtMffDisconnected = u"evt/mff/disconnected";
inline constexpr QStringView kEvtMffPosition     = u"evt/mff/position";
//inline constexpr QStringView kEvtMffStatus       = u"evt/mff/status";
inline constexpr QStringView kEvtMffLog          = u"evt/mff/log";
inline constexpr QStringView kEvtMffError        = u"evt/mff/error";



// 统一payload schema：{"ts", "topic", "payload"}
inline QVariantMap makeEnvelope(QStringView topic, const QVariantMap& payload) {
    QVariantMap env;
    env.insert("ts", QDateTime::currentDateTimeUtc().toMSecsSinceEpoch());
    env.insert("topic", QString(topic));      // 视图 → QString，一次性存盘用
    env.insert("payload", payload);
    return env;
}
} // namespace Events
