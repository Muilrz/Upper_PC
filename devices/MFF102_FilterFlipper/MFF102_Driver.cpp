#include "MFF102_Driver.h"


#include "ThorLabs.MotionControl.FilterFlipper.h"

static QStringList splitSerials(const char* csv)
{
    QString s = QString::fromLatin1(csv).trimmed();
    if (s.isEmpty()) return {};
    QStringList out;
    for (auto& part : s.split(',', Qt::SkipEmptyParts))
        out << part.trimmed();
    return out;
}

bool MFF102_Driver::init(QString* err)
{
#if MFF_USE_SIMULATION

    TLI_InitializeSimulations();
    simInited_ = true;
#endif
    return true;
}


void MFF102_Driver::shutdown()
{
#if MFF_USE_SIMULATION
    if (simInited_) {
        TLI_UninitializeSimulations();
        simInited_ = false;
    }
#endif
}


QStringList MFF102_Driver::refreshDevices(QString* err)
{
    if (TLI_BuildDeviceList() != 0) {
        if (err) *err = "TLI_BuildDeviceList 失败（设备被占用/驱动异常常见）";
        // 不中断，继续尝试拿列表
    }

    char serialNos[1024] = {0};
    if (TLI_GetDeviceListByTypeExt(serialNos, sizeof(serialNos), 37) != 0) {
        if (err) *err = "TLI_GetDeviceListByTypeExt 失败";
        return {};
    }
    return splitSerials(serialNos);
}

bool MFF102_Driver::open(const QString& serial, QString* err)
{
    QByteArray s = serial.toLatin1();
    short r = FF_Open(s.constData());
    if (r != 0) {
        if (err) *err = QString("FF_Open 失败, code=%1").arg(r);
        return false;
    }
    serial_ = serial;
    opened_ = true;
    return true;
}

void MFF102_Driver::close()
{
    if (!opened_) return;
    QByteArray s = serial_.toLatin1();
    FF_Close(s.constData());
    opened_ = false;
    serial_.clear();
}

bool MFF102_Driver::startPolling(int intervalMs, QString* err)
{
    if (!opened_) { if (err) *err = "未连接设备"; return false; }
    QByteArray s = serial_.toLatin1();
    if (!FF_StartPolling(s.constData(), intervalMs)) {
        if (err) *err = "FF_StartPolling 返回 false";
        return false;
    }
    return true;
}

void MFF102_Driver::stopPolling()
{
    if (!opened_) return;
    QByteArray s = serial_.toLatin1();
    FF_StopPolling(s.constData());
}

bool MFF102_Driver::flipTo(int pos12, QString* err)
{
    if (!opened_) { if (err) *err = "未连接设备"; return false; }


    QByteArray s = serial_.toLatin1();
    FF_Positions target = (pos12 == 1) ? FF_Positions::Position1 : FF_Positions::Position2;
    short r = FF_MoveToPosition(s.constData(), target);


    if (r != 0) {
        if (err) *err = QString("FF_MoveToPosition 失败, code=%1").arg(r);
        return false;
    }
    return true;
}

int MFF102_Driver::getPosition(QString* err)
{
    if (!opened_) { if (err) *err = "未连接设备"; return -1; }
    QByteArray s = serial_.toLatin1();
    FF_RequestStatus(s.constData());
    return (int)FF_GetPosition(s.constData());

}

int MFF102_Driver::getTransitTime(QString* err)
{
    if (!opened_) { if (err) *err = "未连接设备"; return -1; }
    QByteArray s = serial_.toLatin1();

    // 直接读 DLL 里的 transit time（单位：ms）
    int t = (int)FF_GetTransitTime(s.constData());

    // 防御：有时没初始化好会给 0 或负数
    if (t <= 0) t = 1000; // 给个合理默认
    return t;
}

/*
quint32 MFF102_Driver::getStatusBits(QString* err)
{
    if (!opened_) { if (err) *err = "未连接设备"; return 0; }
    QByteArray s = serial_.toLatin1();
    FF_RequestStatus(s.constData());
    return (quint32)FF_GetStatusBits(s.constData());
*/

void MFF102_Driver::clearMessageQueue()
{
    if (!opened_) return;
    QByteArray s = serial_.toLatin1();
    FF_ClearMessageQueue(s.constData());
}

bool MFF102_Driver::home(QString* err)
{
    if (!opened_) { if (err) *err = "未连接设备"; return false; }
    QByteArray s = serial_.toLatin1();
    short r = FF_Home(s.constData());
    if (r != 0) { if (err) *err = QString("FF_Home 失败, code=%1").arg(r); return false; }
    return true;
}

