#include "mainwindow.h"
#include "ScannerSim.h"
#include <QApplication>
#include "SerialBridge.h"
#include <QThread>
#include "MFF102_FilterFlipper/MFF102_Bridge.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScannerSim sim;
    SerialBridge serial;

    // 启动 MFF102 Bridge（后台线程）
    auto* mff = new MFF102_Bridge;
    auto* t = new QThread(&a);
    mff->moveToThread(t);

    QObject::connect(&a, &QCoreApplication::aboutToQuit, t, &QThread::quit);
    QObject::connect(t, &QThread::finished, mff, &QObject::deleteLater);
    t->start();

    MainWindow w;
    w.show();
    return a.exec();
}


