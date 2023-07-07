#include "DeviceDriver.h"
#include "Windows.h"
#include <stdexcept>
using namespace std;

// Custom Exception class for Read failure
class ReadFailException : public runtime_error {
public:
    ReadFailException() : runtime_error("Read failed: Values are not identical.") {}
};

class WriteFailException : public runtime_error {
public:
    WriteFailException() : runtime_error("Write failed: Value already exists at the given address.") {}
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
    if (read(address) != 0xFF)
    {
        throw WriteFailException();
    }
    // TODO: implement this method
    m_hardware->write(address, (unsigned char)data);
}

/* °­»ç´Ô ÄÚµå
* #include "DeviceDriver.h"

#include <exception>

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

class ReadFailException : public std::exception {};
class WriteFailException : public std::exception {};

int DeviceDriver::read(long address)
{
    int result = (int)(m_hardware->read(address));

	const int RETRY_COUNT = 4;
    for (int i = 0; i < RETRY_COUNT; i++) {
        if (result == (int)m_hardware->read(address)) continue;
        throw ReadFailException();
    }
    return result;
}

void DeviceDriver::write(long address, int data)
{
    if ((int)m_hardware->read(address) != 0xFF) {
        throw WriteFailException();
    }
    m_hardware->write(address, (unsigned char)data);

}
*/