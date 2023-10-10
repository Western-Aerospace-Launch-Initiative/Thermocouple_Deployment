#include <gtest/gtest.h>

extern "C"{
        #include "../../MCP9600.h"
}

TEST(MCP9600_Tests, mcp_thermocouple_init_function){
    i2c_thermocouple* pdevice;
    pdevice = mcp_thermocouple_init(1, 0x67, K_TYPE, "Init Device");

    ASSERT_EQ(pdevice->i2c_bus_int, 1);
    ASSERT_EQ(pdevice->i2c_address, 0x67);
    ASSERT_EQ(pdevice->filedes, -1);
    ASSERT_EQ(pdevice->thermocouple_type, K_TYPE);
    ASSERT_EQ(pdevice->enabled, 0);
    ASSERT_STREQ(pdevice->ID, "Init Device");
}

TEST(MCP9600_Tests, mcp_device_enable_function){
    i2c_thermocouple* pdevice; 
    pdevice = mcp_thermocouple_init(2, 0x70, K_TYPE, "en_device");
     
    mcp_thermocouple_enable(pdevice);

    // Find a new way to test this. This internal API is unsupported
    /*
    {
        testing::internal::CaptureStderr();
        std::string CapturedError = testing::internal::GetCapturedStderr();
        std::string ExpectedError = "ERROR 8: The device \"en_device\" is already enabled.";
        std::string str;
        EXPECT_PRED3([](auto str, auto CapturedError, auto ExpectedError) {
            return str == CapturedError || str == ExpectedError;}, 
            str, CapturedError, ExpectedError);
    }
    */

    // Fix error
    pdevice->enabled = 0;

    // Check device is enabled
    ASSERT_EQ(mcp_thermocouple_enable(pdevice), 0);
    
    // Verify Correct Values
    ASSERT_EQ(pdevice->i2c_address, 0x70);
    ASSERT_EQ(pdevice->thermocouple_type, K_TYPE);
    ASSERT_EQ(pdevice->enabled, 1); // Only value that should change
    ASSERT_STREQ(pdevice->ID, "en_device");
    close(pdevice->filedes);

}

TEST(MCP9600_Tests, mcp_device_disable_function) {
    i2c_thermocouple* pdevice;
    pdevice = mcp_thermocouple_init(2, 0x69, K_TYPE, "di_test");
    
    mcp_thermocouple_disable(pdevice);

    /*
    {
        testing::internal::CaptureStderr();
        std::string CapturedError = testing::internal::GetCapturedStderr();
        std::string ExpectedError = "ERROR 3: The device \"di_test\" \
        is not enabled. Please enable it before continuing.";
        std::string str;
        EXPECT_PRED3([](auto str, auto CapturedError, auto ExpectedError) {
            return str == CapturedError || str == ExpectedError;}, 
            str, CapturedError, ExpectedError);
    }
    */

    mcp_thermocouple_enable(pdevice);

    EXPECT_EQ(mcp_thermocouple_disable(pdevice), 0);  
    
    // Verify values
    EXPECT_EQ(pdevice->i2c_bus_int, 2);
    EXPECT_EQ(pdevice->i2c_address, 0x69);
    EXPECT_EQ(pdevice->filedes, -1);
    EXPECT_EQ(pdevice->thermocouple_type, K_TYPE);
    EXPECT_EQ(pdevice->enabled, 0);
    EXPECT_STREQ(pdevice->ID, "di_test");
    
}

TEST(MCP9600_Tests, mcp_get_temp_function) {
    i2c_thermocouple* device; 

    device = mcp_thermocouple_init(2, 0x60, K_TYPE, "temp_test");
    mcp_thermocouple_enable(device);
    EXPECT_GT(mcp_get_temp(device), 10.0); //Terrible tests find a better way to do it
    EXPECT_LT(mcp_get_temp(device), 40.0);
    mcp_thermocouple_disable(device);
}

TEST(MCP9600_Tests, mcp_get_status_function){
    i2c_thermocouple* pdevice;
    pdevice = mcp_thermocouple_init(2, 0x60, K_TYPE, "status_test");
    EXPECT_EQ(mcp_get_status(pdevice), 0xff);

    /*
    {
        testing::internal::CaptureStderr();
        std::string CapturedError = testing::internal::GetCapturedStderr();
        std::string ExpectedError = "ERROR 2: The device \"status_test\" is not enabled. Please enable it before continuing.\n";
        std::string str;
        EXPECT_PRED3([](auto str, auto CapturedError, auto ExpectedError) {
            return str == CapturedError || str == ExpectedError;}, 
            str, CapturedError, ExpectedError);
    }
    */

    mcp_thermocouple_enable(pdevice);
    EXPECT_EQ(mcp_get_status(pdevice), 0x4f);
}
