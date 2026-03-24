#pragma once
#include <QObject>
#include <QSettings>

class Config : public QObject {
    Q_OBJECT
public:
    explicit Config(QObject* parent=nullptr);
    // 示例参数：扫描范围、速度、抬针高度
    double scanRangeXY() const;      void setScanRangeXY(double v);
    double scanSpeed() const;        void setScanSpeed(double v);
    double liftHeightNm() const;     void setLiftHeightNm(double v);
private:
    QSettings st_;
};

