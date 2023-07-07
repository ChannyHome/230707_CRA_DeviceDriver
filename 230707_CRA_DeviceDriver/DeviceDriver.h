#pragma once
#include "FlashMemoryDevice.h"
//#define MAX_READ_COUNT 5

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    int read(long address);
    void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;

private:
    const int MAX_READ_COUNT = 5;
    const int READ_INTERVAL = 200;
};