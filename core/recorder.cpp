#include "recorder.h"

Recorder::Recorder(QObject* parent) : QObject(parent) {}

bool Recorder::open(const QString& path) {
    QMutexLocker lk(&mtx_);
    file_.setFileName(path);
    return file_.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text);
}

void Recorder::writeEvent(const QVariantMap& env) {
    QMutexLocker lk(&mtx_);
    if (!file_.isOpen()) return;
    QJsonDocument doc = QJsonDocument::fromVariant(env);
    file_.write(doc.toJson(QJsonDocument::Compact));
    file_.write("\n");
    file_.flush();
}
