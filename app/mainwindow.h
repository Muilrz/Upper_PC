#pragma once
#include <QMainWindow>
#include <QPointer>
#include <QSerialPort>
#include <QByteArray>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class EventBus;
class Logger;
class Recorder;
class ExperimentFsm;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartClicked();
    void onStopClicked();
    void onResetClicked();
    void onPauseClicked();
    void onContinueClicked();
    void onRefreshPorts();
    void onOpenClosePort();
    void onSendToOled();


private:
    Ui::MainWindow *ui;           // Qt Designer UI 对象
    QPointer<EventBus> bus_;
    QPointer<Logger> logger_;
    QPointer<Recorder> recorder_;
    QPointer<ExperimentFsm> fsm_;
    QSerialPort* serial_ = nullptr;
    QByteArray rxBuf_;
    void setupSerial();

    void connectUi();
    void setupEventSubscriptions();

    bool mffConnected_ = false;
};


