#pragma once
#include <QObject>
#include <QFile>
#include <QMutex>
#include <QJsonDocument>
#include <QVariantMap>

class Recorder : public QObject {
    Q_OBJECT
public:
    explicit Recorder(QObject* parent=nullptr);
    bool open(const QString& path); // .jsonl
    void writeEvent(const QVariantMap& envelope); // {ts, topic, payload}
private:
    QFile file_;
    QMutex mtx_;
};
