#pragma once
#include <QObject>
#include <QFile>
#include <QMutex>
#include <QTextStream>

class Logger : public QObject {
    Q_OBJECT
public:
    explicit Logger(QObject* parent=nullptr);
    bool open(const QString& path);
    void logLine(const QString& line); // 线程安全
signals:
    void lineAppended(const QString& line);
private:
    QFile file_;
    QMutex mtx_;
};
