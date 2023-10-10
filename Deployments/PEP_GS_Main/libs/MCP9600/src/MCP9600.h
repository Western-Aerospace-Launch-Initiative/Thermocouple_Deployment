/****************************
 * MCP9600.h
 *
 * Version 1.0.0
 *
 * Noah Braasch 2023
 *
 ****************************/

#pragma once

#ifndef _MCP_THERMOCOUPLE_H
#define _MCP_THERMOCOUPLE_H

/*! BUFFER_SIZE 
 * is a macro that is used to define the size of strings whose
 * declarations require a specific size at compile time.
 */
#define BUFFER_SIZE 12 //Buffer size for accessing /dev/i2c-*

/*! K_TYPE 
 * is a macro that describes the type of thermocouple used on the
 * cooresponding device. The value 0x00 comes from the datasheet for the 
 * MCP9600. It is worth nothing that this macro initialises the MCP9600
 * with no filter enabed.
 */
#define K_TYPE 0x00 // K-Type Thermocouple with no filter

/*! HOT_JUNCTION_TEMPERATURE_REGISTER 
 * is a macro that references a hex 
 * value 0x00, which is the address for the hot junction register of the 
 * MCP9600.
 */
#define HOT_JUNCTION_TEMPERATURE_REGISTER 0x00

/*! STATUS_REGISTER 
 * is a macro that references a hex 
 * value 0x04, which is the address for the status register of the 
 * MCP9600.
 */
#define STATUS_REGISTER 0x04

/*! THERMOCOUPLE_SENSOR_TYPE_REGISTER 
 * is a macro that references a hex 
 * value 0x05, which is the address for the thermocouple type confgiration 
 * register of the MCP9600.
 */
#define THERMOCOUPLE_SENSOR_TYPE_REGISTER 0x05

/*! DEVICE_CONFIG_REGISTER 
 * is a macro that references a hex 
 * value 0x06, which is the address for the device confgiration 
 * register of the MCP9600.
 */
#define DEVICE_CONFIG_REGISTER 0x06

/*! NORMAL_MODE 
 * is a macro that references a hex 
 * value 0x00, which is the value for normal operation mode with 0.0625 degree
 * cold junction resolution and 18-bit ADC resolution
 */
#define NORMAL_MODE 0x00

/*! SHUTDOWN_MODE 
 * is a macro that references a hex 
 * value 0x01, which is the value for shutdown operation mode with 0.0625 degree
 * cold junction resolution and 18-bit ADC resolution
 */
#define SHUTDOWN_MODE 0x01

/*! BURST_MODE 
 * is a macro that references a hex 
 * value 0x02, which is the value for burst operation mode with 0.0625 degree
 * cold junction resolution and 18-bit ADC resolution
 */
#define BURST_MODE 0x02

/*! INIT_FILES 
 * is a macro that references a -1. This is the value used to clear 
 * file designator values of i2c_thermocouple device
 *
 * @see struct i2c_thermocouple
 */
#define INIT_FILEDES -1


/*! LOW_TEMP 
 * is a macro that references a hex value 0x80. 
 * This is the value used with a bitwise & operator to determine which 
 * temperature conversion formula to use.
 *
 * @see mcp_get_temp()
 * @see struct i2c_thermocouple
 */
#define LOW_TEMP 0x80

/*! HALF_SECOND 
 * is a macro that references an int value 500000. This is 
 * used in the stdlib usleep() function to sleep for 500000 microseconds or 
 * half a second. This allows for the thermocouple to wake from shutdown mode 
 * before giving access back to the user to prevent trying to read the device
 * termperature before the temperature register can update.
 * 
 * @see mcp_thermocouple_enable()
 */
#define HALF_SECOND 500000

#define ERROR_0 "ERROR 0: The device \"%s\" was unable to be opened.\n", bus
#define ERROR_1 "ERROR 1: The device address \"%d\" was found to be invalid.\n", pdevice->i2c_address
#define ERROR_2 "ERROR 2: The device \"%s\" is not enabled. Please enable it before continuing.\n", pdevice->ID
#define ERROR_3 "ERROR 3: Device \"%s\" was unable to close.\n", pdevice->ID
#define ERROR_4 "ERROR 4: Temperature read failed.\n"
#define ERROR_5 "ERROR 5: Device \"%s\" read failed.\n", pdevice->ID
#define ERROR_6 "ERROR_6: Device \"%s\" write failed.\n", pdevice->ID
#define ERROR_7 "ERROR_7: Device ID is larger than %d characters. Please shorten it.\n", BUFFER_SIZE
#define ERROR_8 "ERROR 8: The device \"%s\" is already enabled.\n", pdevice->ID

/*! MCP_CONFIGURE 
 * is a macro that writes 2 bytes to a specific MCP9600 
 * device register. 
 *
 * @param DEVICE is an open file designator. Often this will be 
 * pdevice->filedes.
 *
 * @param DEVICE_CONFIG_REGISTER is the register to which you would like to 
 * write.
 * 
 * @param REGISTER_VALUE is the value that will be written to the register.
 * This is often a macro defined in this library.
 *
 * @see mcp_open_i2c_bus()
 * */
#define MCP_CONFIGURE(DEVICE, DEVICE_CONFIG_REGISTER, REGISTER_VALUE) {\
        {\
            char config[2];\
            config[0] = DEVICE_CONFIG_REGISTER;\
            config[1] = REGISTER_VALUE;\
            write(DEVICE, config, 2);\
            }\
        }

/*! i2c_thermocouple 
 * is a struct that hold all neccesary parameters of 
 * an MCP9600 thermocouple device. 
 * */
typedef struct {
    int i2c_bus_int; /*!< an integer that stores the i2c bus*/
    int i2c_address; /*!< an integer that stores the i2c address*/
    int filedes; /*!< an integer that stores the file designator */
    char thermocouple_type; /*!< a char that stores the thermocouple type*/
    char enabled;/*!< a char that stores the enabled status*/ 
    const char* ID; /*!< a string that stores the device ID*/ 
} i2c_thermocouple;


#ifdef __cplusplus
extern "C"{
#endif

i2c_thermocouple* mcp_thermocouple_init(
    int i2c_bus_int,
    int i2c_address,
    char thermocouple_type,
    const char* ID
    );

int mcp_thermocouple_enable(i2c_thermocouple* pdevice);

int mcp_thermocouple_disable(i2c_thermocouple* pdevice);

float mcp_get_temp(i2c_thermocouple* pdevice);

char mcp_get_status(i2c_thermocouple* pdevice);

static int mcp_open_i2c_bus(i2c_thermocouple* pdevice);

static int mcp_close_i2c_bus(i2c_thermocouple* pdevice);

static void mcp_thermocouple_configure(i2c_thermocouple* pdevice);

static char* mcp_thermocouple_bus_to_string(int i2c_bus);

#ifdef __cplusplus
}
#endif


#endif /* _MCP_THERMOCOUPLE_H */
