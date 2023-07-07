#include "DeviceDriver.h"
#include <vector>
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
			string addressStr = "Address : " + addr;
			string valStr = ", Value : " + value;
			cout << addressStr + valStr << std::endl;
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