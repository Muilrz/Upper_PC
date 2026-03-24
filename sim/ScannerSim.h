#pragma once
#include <QObject>
#include <QTimer>


class ScannerSim : public QObject {
    Q_OBJECT
public:
    explicit ScannerSim(QObject* parent=nullptr);
private slots:
    void onTick();
private:
    QTimer timer_;
    int progress_ = 0;
    bool running_ = false;
    void wireBus();
};
