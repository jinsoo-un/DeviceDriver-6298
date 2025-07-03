#pragma once
#include "flash_memory_device.h"
#include "gmock/gmock.h"

#define TestTryCount (4)

class DeviceDriver
{
public:
    DeviceDriver(FlashMemoryDevice* hardware);
    virtual int read(long address);
    void postConditionCheck(int ret, long address);
    void preconditionCheck(long address);
    virtual void write(long address, int data);

protected:
    FlashMemoryDevice* m_hardware;
};


class MockDeviceDriver : public DeviceDriver {
public:
	MockDeviceDriver(FlashMemoryDevice* hardware) : DeviceDriver(hardware) {}
	MOCK_METHOD(int, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, int data), (override));
};
