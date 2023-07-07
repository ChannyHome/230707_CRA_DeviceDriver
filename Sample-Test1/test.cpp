#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include "../230707_CRA_DeviceDriver/DeviceDriver.cpp"
using namespace testing;
using namespace std;

//Mock ��ü
class FlashMock : public FlashMemoryDevice {

public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};


TEST(TestDeviceDriver, testRead) {

	FlashMock mockDevice;
	EXPECT_CALL(mockDevice, read).Times(5);
	//
	DeviceDriver device(&mockDevice);
	device.read(0xA);

	//	EXPECT_CALL(mock, getDBName())
	//.WillRepeatedly(Return(""));
}

TEST(TestDeviceDriver, testReadFailException) {
    FlashMock mockDevice;
    EXPECT_CALL(mockDevice, read)
        .WillOnce(Return(999))
        .WillOnce(Return(888));

    DeviceDriver device(&mockDevice);

    try {
        device.read(0xA);
        FAIL() << "Expected ReadFailException to be thrown.";
    }
    catch (const ReadFailException& e) {
        SUCCEED();
    }
    catch (...) {
        FAIL() << "Unexpected exception thrown.";
    }
}

TEST(TestDeviceDriver, testWriteFailException) {

	FlashMock mockDevice;
	EXPECT_CALL(mockDevice, read)
		.WillRepeatedly(Return(999));
	//
	DeviceDriver device(&mockDevice);
	device.read(0xB);

    try {
        device.write(0xB,111);
        FAIL() << "Expected ReadFailException to be thrown.";
    }
    catch (const WriteFailException& e) {
        SUCCEED();
    }
    catch (...) {
        FAIL() << "Unexpected exception thrown.";
    }
}



TEST(TestDeviceDriver, testWriteNoFailException) {

    FlashMock mockDevice;
    EXPECT_CALL(mockDevice, read)
        .WillRepeatedly(Return(0xFF));
    //
    DeviceDriver device(&mockDevice);
    device.read(0xB);

    try {
        device.write(0xB, 111);
        SUCCEED();
    }
    catch (const WriteFailException& e) {
        FAIL() << "Expected WriteFailException to be thrown.";
    }
    catch (...) {
        FAIL() << "Unexpected exception thrown.";
    }
}



