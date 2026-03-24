#pragma once
#include <string>

struct OpenResult {
    bool ok{false};
    std::string message;
};

class IDevice {
public:
    virtual ~IDevice() = default;
    virtual OpenResult open() = 0;
    virtual void close() = 0;
    virtual bool isOpen() const = 0;
    virtual const char* name() const = 0;
};
