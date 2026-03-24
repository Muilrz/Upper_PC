#ifndef MFF1_2_BRIDGE_H
#define MFF1_2_BRIDGE_H
#pragma once
#include <QObject>
#include <QTimer>
#include "MFF102_Driver.h"

class MFF102_Bridge : public QObject {
    Q_OBJECT
public:
    explicit MFF102_Bridge(QObject* parent=nullptr);
    ~MFF102_Bridge() override;

private:
    MFF102_Driver driver_;




    void log(const QString& s);
    void error(const QString& s);
};


#endif
