#include "gmock/gmock.h"
#include "device_driver.h"
#include "application.cpp"

using namespace testing;

class FlashMock : public FlashMemoryDevice {
public:
    MOCK_METHOD(unsigned char, read, (long address), (override));
    MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

TEST(TS, TC5) {
    NiceMock<FlashMock> mockHW;
    DeviceDriver dd{ &mockHW };
    Application app{ &dd };

    EXPECT_CALL(mockHW, read(_))
        .Times(25)
        .WillRepeatedly(Return(0xFA));

    app.readAndPrint(0x00, 0x04);
}

TEST(TS, TC6) {
    NiceMock<FlashMock> mockHW;
    DeviceDriver dd{ &mockHW };
    Application app{ &dd };

    EXPECT_CALL(mockHW, read(_))
        .Times(5)
        .WillRepeatedly(Return(0xFF));

    app.writeAll(0xA7);
}

TEST(TS, TC4) {
    NiceMock<FlashMock> mockHW;
    DeviceDriver dd{ &mockHW };

    EXPECT_CALL(mockHW, read((long)0xA))
        .Times(1)
        .WillOnce(Return(0xFA));

    EXPECT_THROW(dd.write((long)0xA, 0x33),
        std::exception);
}

TEST(TS, TC3) {
    NiceMock<FlashMock> mockHW;
    DeviceDriver dd{ &mockHW };

    EXPECT_CALL(mockHW, read((long)0xA))
        .Times(1)
        .WillOnce(Return(0xFF));

    dd.write((long)0xA, 0x33);
}

TEST(TS, TC2) {
    FlashMock mockHW;
    DeviceDriver dd{ &mockHW };

    EXPECT_CALL(mockHW, read((long)0xA))
        .WillOnce(Return((int)0xDD))
        .WillOnce(Return((int)0xDD))
        .WillOnce(Return((int)0xDD))
        .WillOnce(Return((int)0xDD))
        .WillOnce(Return((int)0xDA));

    EXPECT_THROW(dd.read(0xA), std::exception);
}

TEST(TS, TC1) {
    FlashMock mockHW;
    DeviceDriver dd{ &mockHW }; //mock injection

    EXPECT_CALL(mockHW, read((long)0xA))
        .Times(5)
        .WillRepeatedly(Return((int)0x77));

    int result = dd.read(0xA);
}

int main() {
    ::testing::InitGoogleMock();
    return RUN_ALL_TESTS();
}