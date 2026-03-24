#include "config.h"

Config::Config(QObject* parent) : QObject(parent), st_("UpperPC", "UpperPC") {}

double Config::scanRangeXY() const { return st_.value("scan/range_xy", 1000.0).toDouble(); }
void   Config::setScanRangeXY(double v){ st_.setValue("scan/range_xy", v); }

double Config::scanSpeed() const   { return st_.value("scan/speed", 200.0).toDouble(); }
void   Config::setScanSpeed(double v){ st_.setValue("scan/speed", v); }

double Config::liftHeightNm() const{ return st_.value("scan/lift_nm", 5.0).toDouble(); }
void   Config::setLiftHeightNm(double v){ st_.setValue("scan/lift_nm", v); }
