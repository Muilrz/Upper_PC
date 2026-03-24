#pragma once
#include <QObject>
#include <QSerialPort>
#include <QByteArray>

class SerialBridge : public QObject
{
    Q_OBJECT
public:
    explicit SerialBridge(QObject* parent = nullptr);

private:
    QSerialPort port_;
    QByteArray rxBuf_;

    void wireBus();
    static QVariantMap unwrapPayload(const QVariant& v);

private slots:
    void onReadyRead();
    void onError(QSerialPort::SerialPortError err);
};
