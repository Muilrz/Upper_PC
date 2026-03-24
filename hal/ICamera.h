#pragma once
#include "IDevice.h"
#include <cstdint>
#include <vector>

struct Frame {
    int width{0}, height{0};
    long long seq{0};
    double t_steady{0.0}; // steady_clock 到秒的偏移
    std::vector<uint8_t> pixels; // 灰度占位
};

class ICamera : public IDevice {
public:
    virtual bool startStream(int fps) = 0;
    virtual void stopStream() = 0;
    // 真实实现会用回调/队列，这里接口先保持最小化
};
