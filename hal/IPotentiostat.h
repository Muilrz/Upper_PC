#pragma once
#include "IDevice.h"

enum class ECMode { ChronoAmperometry, CyclicVoltammetry };

class IPotentiostat : public IDevice {
public:
    virtual bool configure(ECMode mode, double v1, double v2, double rate) = 0;
    virtual bool start() = 0;
    virtual void stop() = 0;
};
