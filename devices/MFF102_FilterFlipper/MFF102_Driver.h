#ifndef MFF1_2_DRIVER_H
#define MFF1_2_DRIVER_H
#pragma once
#include <QString>
#include <QStringList>
#include <QtGlobal>

class MFF102_Driver {
public:
    bool init(QString* err = nullptr);     // 模拟模式会调用 TLI_InitializeSimulations
    void shutdown();

    QStringList refreshDevices(QString* err = nullptr);  // 返回序列号列表
    bool open(const QString& serial, QString* err = nullptr);
    void close();

    int getTransitTime(QString* err = nullptr);

    bool startPolling(int intervalMs, QString* err = nullptr);
    void stopPolling();

    bool flipTo(int pos12, QString* err = nullptr);      // 1 或 2
    int  getPosition(QString* err = nullptr);            // 可能 0（运动中）
//  quint32 getStatusBits(QString* err = nullptr);      //暂时不需要getStatus，所以注释掉了Driver和 Bridge里所有的getStatus函数和cmd/evt

    bool isOpen() const { return opened_; }
    QString serial() const { return serial_; }

    void clearMessageQueue();
    bool home(QString* err = nullptr);


private:
    QString serial_;
    bool opened_ = false;
    bool simInited_ = false;


};

#endif // MFF1_2_DRIVER_H
