#pragma once
#include "IDevice.h"
#include <vector>

struct PathPoint { double x; double y; double t; }; // t: 计划时间（秒）

class IScanner : public IDevice {
public:
    virtual bool loadPath(const std::vector<PathPoint>& path) = 0;
    virtual bool start() = 0;    // 软触发开始
    virtual void stop() = 0;
};
