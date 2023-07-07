#include "DeviceDriver.h"
#include "Windows.h"
#include <stdexcept>
using namespace std;

// Custom Exception class for Read failure
class ReadFailException : public runtime_error {
public:
    ReadFailException() : runtime_error("Read failed: Values are not identical.") {}
};

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method properly
    int result = 0;
    int current = 0;
    for (int i = 0; i < MAX_READ_COUNT; i++)
    {
        if(i == 0)
            result = (int)(m_hardware->read(address));
        else
            if (result != (int)(m_hardware->read(address)))
            {
                throw ReadFailException();
            }

        Sleep(READ_INTERVAL);
    }
    return result;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}