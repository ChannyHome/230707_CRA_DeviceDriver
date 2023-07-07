#include "DeviceDriver.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;

class App
{
public:
	App(DeviceDriver* driver) : driver(driver)
	{}
	void ReadAndPrint(long startAddr, long endAddr)
	{
		for (long addr = startAddr; addr <= endAddr; addr++) {
			int value = driver->read(addr);
			//string addressStr = "Address: " + to_string(addr);
			//string valStr = ", Value: " + to_string(value);
			//cout << addressStr + valStr << std::endl;
			cout << "Address: " << hex << addr << ", Value: " << dec << value << endl;
		}
	}
	void WriteAll(int value)
	{
		for (long temp : addressMap)
		{
			driver->write(temp, value);
		}
	}

private:
	DeviceDriver* driver;
	const vector<long> addressMap = { '0x00', '0x01', '0x02', '0x03', '0x04' };
};