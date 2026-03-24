#include "logger.h"
#include <QDateTime>

Logger::Logger(QObject* parent) : QObject(parent) {}

bool Logger::open(const QString& path) {
    QMutexLocker lk(&mtx_);
    file_.setFileName(path);
    return file_.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
}

void Logger::logLine(const QString& line) {
    const QString ts = QDateTime::currentDateTime().toString(Qt::ISODateWithMs);
    const QString out = ts + " " + line + "\n";
    {
        QMutexLocker lk(&mtx_);
        if (file_.isOpen()) {
            file_.write(out.toUtf8());
            file_.flush();
        }
    }
    emit lineAppended(out);
}
