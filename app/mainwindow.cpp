#include "mainWindow.h"
#include "ui_mainwindow.h"

#include "core/events.h"
#include "core/logger.h"
#include "core/recorder.h"
#include "core/fsm/ExperimentFsm.h"
#include "EventBus.h"

#include <QJsonDocument>
#include <QMessageBox>
#include <QSerialPort>
#include <QSerialPortInfo>

#include <QDir>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    bus_ = &EventBus::instance();



    ui->cmbBaud->addItem("9600", 9600);
    ui->cmbBaud->addItem("115200", 115200);
    ui->cmbBaud->setCurrentText("9600");


    //先确定是否生成logs目录
    QString logDir = QCoreApplication::applicationDirPath() + "/logs";
    QDir().mkpath(logDir);

    // 启动日志系统
    logger_ = new Logger(this);
    logger_->open(logDir + "/app.log");
    logger_->logLine("Logger started");

    // 启动事件记录器
    recorder_ = new Recorder(this);
    recorder_->open(logDir + "/events.jsonl");
    recorder_->writeEvent({
        {"ts", QDateTime::currentDateTimeUtc().toMSecsSinceEpoch()},
        {"topic", "sys/start"},
        {"payload", QVariantMap{}}
    });

    // 用单例
    fsm_ = new ExperimentFsm(&EventBus::instance(), this);



    connectUi();
    setupEventSubscriptions();


}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::connectUi()
{
    // 按钮信号槽连接
    connect(ui->btnStart, &QPushButton::clicked, this, &MainWindow::onStartClicked);
    connect(ui->btnStop,  &QPushButton::clicked, this, &MainWindow::onStopClicked);
    connect(ui->btnReset, &QPushButton::clicked, this, &MainWindow::onResetClicked);
    connect(ui->btnPause, &QPushButton::clicked, this, &MainWindow::onPauseClicked);
    connect(ui->btnContinue, &QPushButton::clicked, this, &MainWindow::onContinueClicked);
    connect(ui->btnRefreshPorts, &QPushButton::clicked, this, &MainWindow::onRefreshPorts);
    connect(ui->btnOpenPort, &QPushButton::clicked, this, &MainWindow::onOpenClosePort);
    connect(ui->btnSend, &QPushButton::clicked, this, &MainWindow::onSendToOled);

    connect(ui->btnMffRefresh, &QPushButton::clicked, this, []() {
        EventBus::instance().publish(Events::kCmdMffRefresh);
    });

    connect(ui->btnMffConnect, &QPushButton::clicked, this, [this]() {
        if (!mffConnected_) {
            EventBus::instance().publish(Events::kCmdMffConnect,
                                         QVariantMap{{"serial", ui->cmbMffSerial->currentText()}});
        } else {
            EventBus::instance().publish(Events::kCmdMffDisconnect);
        }
    });

    connect(ui->btnMffStartPolling, &QPushButton::clicked, this, []() {
        EventBus::instance().publish(Events::kCmdMffStartPolling,
                                     QVariantMap{{"interval_ms", 200}});
    });
    connect(ui->btnMffStopPolling, &QPushButton::clicked, this, []() {
        EventBus::instance().publish(Events::kCmdMffStopPolling);
    });
    connect(ui->btnMffPos1, &QPushButton::clicked, this, []{
        qDebug() << "[UI] Pos1 clicked";
        EventBus::instance().publish(Events::kCmdMffFlip, QVariantMap{{"pos", 1}});
    });
    connect(ui->btnMffPos2, &QPushButton::clicked, this, []{
        qDebug() << "[UI] Pos2 clicked";
        EventBus::instance().publish(Events::kCmdMffFlip, QVariantMap{{"pos", 2}});
    });

    connect(ui->btnMffReadPos, &QPushButton::clicked, this, []() {
        EventBus::instance().publish(Events::kCmdMffReadPosition);
    });
    /*
    connect(ui->btnMffReadStatus, &QPushButton::clicked, this, []() {
        EventBus::instance().publish(Events::kCmdMffReadStatus);
    });
*/
}

void MainWindow::setupEventSubscriptions()
{
    EventBus& bus = EventBus::instance();

    // 订阅所有事件：写入日志与记录器
    connect(&bus, &EventBus::eventPublished, this,
            [this](const QString& topic, const QVariant& payload) {
        qDebug() << "[UI] got event:" << topic << payload;

                // 封装统一事件 envelope
                QVariantMap env;
                env.insert("topic", topic);
                env.insert("payload", payload);
                recorder_->writeEvent(env);
                logger_->logLine(QString::fromUtf8(
                    QJsonDocument::fromVariant(env)
                        .toJson(QJsonDocument::Compact)
                    ));
            },
            Qt::QueuedConnection);

    // 更新进度条
    connect(&bus, &EventBus::eventPublished, this,
            [this](const QString& topic, const QVariant& payload)
            {
                if (topic == Events::kScanProgress) {
                    const int pct = payload.toMap().value("pct").toInt();
                    QMetaObject::invokeMethod(ui->progressBar,
                                              [this, pct] { ui->progressBar->setValue(pct); },
                                              Qt::QueuedConnection);
                }
            },
            Qt::QueuedConnection);

    // 错误提示
    connect(&bus, &EventBus::eventPublished, this,
            [this](const QString& topic, const QVariant& payload) {
                if (topic == Events::kSysError) {
                    const QString msg = payload.toMap().value("msg").toString();
                    QMetaObject::invokeMethod(this,
                                              [this, msg] {
                                                  QMessageBox::warning(this, "系统错误", msg);
                                              },
                                              Qt::QueuedConnection);
                }
            },
            Qt::QueuedConnection);
    connect(&bus, &EventBus::eventPublished, this,
            [this](const QString& topic, const QVariant& payload) {

                if (topic == Events::kSysReset) {
                    qDebug() << "[UI] received sys/reset -> progress=0";
                    ui->progressBar->setValue(0);
                }

            },
            Qt::QueuedConnection);
    // 串口状态 / 接收显示
    connect(&bus, &EventBus::eventPublished, this,
            [this](const QString& topic, const QVariant& payload) {
                if (topic == Events::kUartStatus) {
                    const auto m = payload.toMap();
                    const QString state = m.value("state").toString();
                    const QString port  = m.value("port").toString();
                    const int baud      = m.value("baud").toInt();

                    ui->lblUartStatus->setText(QString("状态: %1  %2 @ %3").arg(state, port).arg(baud));
                    ui->btnOpenPort->setText(state == "open" ? "关闭" : "打开");
                }
                else if (topic == Events::kUartRx) {
                    const QString text = payload.toMap().value("text").toString();
                    ui->txtRx->appendPlainText("RX: " + text);
                }
            },
            Qt::QueuedConnection);

    // --- MFF102 ---
    connect(&bus, &EventBus::eventPublished, this,
            [this](const QString& topic, const QVariant& payload) {

                if (topic == Events::kEvtMffDevices) {
                    ui->cmbMffSerial->clear();
                    ui->cmbMffSerial->addItems(payload.toStringList());
                }
                else if (topic == Events::kEvtMffConnected) {
                    mffConnected_ = true;
                    const auto m = payload.toMap();
                    ui->btnMffConnect->setText("断开");
                    ui->lblMffStatus->setText(QString("已连接：%1").arg(m.value("serial").toString()));
                }
                else if (topic == Events::kEvtMffDisconnected) {
                    mffConnected_ = false;
                    ui->btnMffConnect->setText("连接");
                    ui->lblMffStatus->setText("未连接");
                }
                else if (topic == Events::kEvtMffPosition) {
                    const auto m = payload.toMap();
                    const int pos = m.value("position").toInt();
                    ui->lblMffStatus->setText(QString("位置：%1").arg(pos));
                }
                /*
                else if (topic == Events::kEvtMffStatus) {
                    const auto m = payload.toMap();
                    const auto bits = (quint32)m.value("statusBits").toULongLong();
                    ui->lblMffStatus->setText(QString("StatusBits: 0x%1").arg(bits, 8, 16, QLatin1Char('0')));
                }
                */
                else if (topic == Events::kEvtMffLog) {

                    ui->txtRx->appendPlainText("[MFF] " + payload.toMap().value("text").toString());
                }
                else if (topic == Events::kEvtMffError) {
                    ui->txtRx->appendPlainText("[MFF][ERR] " + payload.toMap().value("text").toString());
                }
            },
            Qt::QueuedConnection
            );



}


void MainWindow::onStartClicked()
{
    qDebug() << "[UI] Start clicked";
    if (fsm_)
        fsm_->userStart();
}

void MainWindow::onStopClicked()
{
    qDebug() << "[UI] Stop clicked";
    if (fsm_)
        fsm_->userStop();

}

void MainWindow::onResetClicked()
{
    qDebug() << "[UI] Reset clicked";
    if (fsm_)
        fsm_->userReset();
}


void MainWindow::onPauseClicked()
{
    if (fsm_) fsm_->userPause();
}

void MainWindow::onContinueClicked()
{
    if (fsm_) fsm_->userContinue();
}



void MainWindow::onRefreshPorts()
{
    ui->cmbPort->clear();
    const auto ports = QSerialPortInfo::availablePorts();
    for (const auto& p : ports) {
        const QString shown = p.portName() + (p.description().isEmpty() ? "" : ("  (" + p.description() + ")"));
        ui->cmbPort->addItem(shown, p.portName());
    }
    if (ui->cmbPort->count() == 0)
        ui->lblUartStatus->setText("状态: 未检测到串口设备");
}

void MainWindow::onOpenClosePort()
{
    if (!bus_) return;

    const QString portName = ui->cmbPort->currentData().toString();
    const int baud = ui->cmbBaud->currentData().toInt();

    if (ui->btnOpenPort->text() == "打开") {
        QVariantMap p{{"port", portName}, {"baud", baud}};
        bus_->publish(Events::kCmdUartOpen, Events::makeEnvelope(Events::kCmdUartOpen, p));
        ui->txtRx->appendPlainText(QString("TX: [open] %1 @ %2").arg(portName).arg(baud));
    } else {
        bus_->publish(Events::kCmdUartClose, Events::makeEnvelope(Events::kCmdUartClose, {}));
        ui->txtRx->appendPlainText("TX: [close]");
    }
}

void MainWindow::onSendToOled()
{
    if (!bus_) return;

    const QString text = ui->edtTx->text();
    if (text.isEmpty()) return;

    QVariantMap p{{"text", text}};
    bus_->publish(Events::kCmdOledPrint, Events::makeEnvelope(Events::kCmdOledPrint, p));

    ui->txtRx->appendPlainText("TX: " + text);
    ui->edtTx->clear();
}
