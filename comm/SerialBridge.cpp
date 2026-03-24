#include "SerialBridge.h"

#include "EventBus.h"
#include "events.h"

#include <QVariantMap>

SerialBridge::SerialBridge(QObject* parent) : QObject(parent)
{
    connect(&port_, &QSerialPort::readyRead, this, &SerialBridge::onReadyRead);
    connect(&port_, &QSerialPort::errorOccurred, this, &SerialBridge::onError);
    wireBus();
}

QVariantMap SerialBridge::unwrapPayload(const QVariant& v)
{
    const QVariantMap m = v.toMap();
    // 兼容envelope: {"ts","topic","payload"}
    if (m.contains("payload") && m.value("payload").typeId() == QMetaType::QVariantMap)
        return m.value("payload").toMap();
    return m;
}

void SerialBridge::wireBus()
{
    auto& bus = EventBus::instance();

    connect(&bus, &EventBus::eventPublished, this,
            [this](const QString& topic, const QVariant& payload) {

                if (topic == Events::kCmdUartOpen) {
                    const auto p = unwrapPayload(payload);
                    const QString portName = p.value("port").toString();
                    const int baud = p.value("baud").toInt() > 0 ? p.value("baud").toInt() : 9600;

                    if (port_.isOpen()) port_.close();

                    port_.setPortName(portName);
                    port_.setBaudRate(baud);
                    port_.setDataBits(QSerialPort::Data8);
                    port_.setParity(QSerialPort::NoParity);
                    port_.setStopBits(QSerialPort::OneStop);
                    port_.setFlowControl(QSerialPort::NoFlowControl);

                    if (!port_.open(QIODevice::ReadWrite)) {
                        EventBus::instance().publish(Events::kSysError,
                                                     QVariantMap{{"msg", QString("串口打开失败：%1 (%2)").arg(port_.errorString(), portName)}});
                        EventBus::instance().publish(Events::kUartStatus,
                                                     QVariantMap{{"state","closed"},{"port",portName},{"baud",baud}});
                        return;
                    }

                    EventBus::instance().publish(Events::kUartStatus,
                                                 QVariantMap{{"state","open"},{"port",portName},{"baud",baud}});
                }
                else if (topic == Events::kCmdUartClose) {
                    if (port_.isOpen()) port_.close();
                    EventBus::instance().publish(Events::kUartStatus,
                                                 QVariantMap{{"state","closed"},{"port",port_.portName()},{"baud",(int)port_.baudRate()}});
                }
                else if (topic == Events::kCmdUartSend || topic == Events::kCmdOledPrint) {
                    if (!port_.isOpen()) {
                        EventBus::instance().publish(Events::kSysError, QVariantMap{{"msg","串口未打开，无法发送"}});
                        return;
                    }

                    const auto p = unwrapPayload(payload);
                    QString text = p.value("text").toString();
                    if (text.isEmpty()) return;

                    // 行协议：没有换行就补一个（STM32 按 '\n' 判定一条命令）
                    if (!text.endsWith('\n')) text.append('\n');

                    port_.write(text.toUtf8());
                    port_.flush(); // 可选，但对调试更“确定”
                }

            },
            Qt::QueuedConnection);
}

void SerialBridge::onReadyRead()
{
    const QByteArray chunk = port_.readAll();
    if (chunk.isEmpty()) return;


    const QString hex = QString::fromLatin1(chunk.toHex(' '));
    EventBus::instance().publish(Events::kUartRx, QVariantMap{{"text", "[HEX] " + hex}});


    rxBuf_.append(chunk);


    int idx;
    while ((idx = rxBuf_.indexOf('\n')) >= 0) {
        QByteArray line = rxBuf_.left(idx);
        rxBuf_.remove(0, idx + 1);
        if (!line.isEmpty() && line.endsWith('\r')) line.chop(1);

        EventBus::instance().publish(Events::kUartRx,
                                     QVariantMap{{"text", "[LINE] " + QString::fromUtf8(line)}});
    }


    if (rxBuf_.size() > 4096) rxBuf_.clear();
}

void SerialBridge::onError(QSerialPort::SerialPortError err)
{
    if (err == QSerialPort::NoError) return;
    EventBus::instance().publish(Events::kSysError, QVariantMap{{"msg", "串口错误：" + port_.errorString()}});
}
