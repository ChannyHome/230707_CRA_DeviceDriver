#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include "../230707_CRA_DeviceDriver/DeviceDriver.cpp"
#include "../230707_CRA_DeviceDriver/app.cpp"
using namespace testing;
using namespace std;

//Mock °´Ã¼
class FlashMock : public FlashMemoryDevice {

public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TestApp, testReadAndPrint) {

	FlashMock mockDevice;
	EXPECT_CALL(mockDevice, read).Times(10)
		.WillRepeatedly(Return(1));
	//
	DeviceDriver device(&mockDevice);	
	App app(&device);
	app.ReadAndPrint(0x05, 0x06);
}

TEST(TestApp, testWriteAll) {

	FlashMock mockDevice;
	EXPECT_CALL(mockDevice, read)
		.WillRepeatedly(Return(0xFF));
	EXPECT_CALL(mockDevice, write).Times(5);
	
	DeviceDriver device(&mockDevice);
	App app(&device);
	app.WriteAll(5);
}

TEST(TestDeviceDriver, testRead) {

	FlashMock mockDevice;
	EXPECT_CALL(mockDevice, read).Times(5);
	//
	DeviceDriver device(&mockDevice);
	device.read(0xA);
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



/* °­»ç´Ô ÄÚµå
* #include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../Project139/DeviceDriver.cpp";
using namespace testing;

class FlashMock : public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data));
};

TEST(ReadWithMock, ReadFive) {
	FlashMock mockDevice;
	EXPECT_CALL(mockDevice, read)
		.Times(5);

	DeviceDriver dd(&mockDevice);
	dd.read(0xA);
}

TEST(ReadWithMock, ReadException) {
	FlashMock mockDevice;
	EXPECT_CALL(mockDevice, read)
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xA))
		.WillOnce(Return((unsigned char)0xB));

	DeviceDriver dd(&mockDevice);
	EXPECT_THROW(dd.read(11), std::exception);
}

TEST(WriteWithMock, Write) {
	FlashMock mockDevice;
	EXPECT_CALL(mockDevice, read)
		.Times(1)
		.WillRepeatedly(Return(0xFF));

	DeviceDriver dd(&mockDevice);
	dd.write(0xAL, 0xB);
}

TEST(WriteWithMock, WriteException) {
	FlashMock mockDevice;
	EXPECT_CALL(mockDevice, read)
		.WillRepeatedly(Return(0xA));

	DeviceDriver dd(&mockDevice);
	EXPECT_THROW(dd.write(0xA, 0xB), std::exception);
}

*/