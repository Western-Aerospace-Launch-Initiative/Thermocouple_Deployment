/**************************
 * MCP9600.c 
 *
 * Version 1.0.0
 *
 * Noah Braasch 2023
 *
 **************************/

/*!
 * MCP9600.c contains all function definitions for the MCP9600 library
 */

#include <stdlib.h> // Defines printf()
#include <stdio.h> // Defines exit()
#include <string.h> // Defines snprintf()
#include <linux/i2c-dev.h> //Defines I2C_SLAVE
#include <sys/ioctl.h> // Defines ioctl()
#include <fcntl.h> // defines O_RDWR & open()
#include <unistd.h> // Includes sleep() write() and read() and close()

#include "MCP9600.h"

/*! mcp_thermocouple_init() 
 * returns a pointer to an i2c_thermocouple 
 * structure initialized iwht the input parameters as structure values.
 *
 * @param i2c_bus_int is an integer value describing the i2c bus the device is 
 * located on.
 *
 * @param i2c_address is an integer value cooresponding to 
 * the address value of the thermocouple device. 
 *
 * @param thermocouple_type is a char that describes the type of thermocouple
 * the device is using. This library provides macros use here.
 *
 * @param ID is a string 12 characters in length that can be used to identify
 * the device.
 */

i2c_thermocouple* mcp_thermocouple_init(
    int i2c_bus_int,
    int i2c_address,
    char thermocouple_type,
    const char* ID
    ) {

    // Verify ID isnt too long
    if (strlen(ID) > BUFFER_SIZE) {
        fprintf(stderr, ERROR_7);
        return NULL; // Cant return 1 becuase its a pointer
    }

    static i2c_thermocouple device;
    
    device.i2c_bus_int = i2c_bus_int;
    device.i2c_address = i2c_address;
    device.filedes = INIT_FILEDES;
    device.thermocouple_type = thermocouple_type;
    device.ID = ID;
    return &device;
}


/*! mcp_thermocouple_enable() 
 * takes a reference to an inactive i2c_thermocouple
 * structure and enabled it, returning 0 on success. The function sleeps for 
 * half a second before returning to account for device sampling time.  
 * 
 * @param pdevice is a pointer to an initialized but inactive i2c_thermocouple.
 */
int mcp_thermocouple_enable(i2c_thermocouple* pdevice) {
        
    mcp_open_i2c_bus(pdevice);
    pdevice->enabled = 1;
    usleep(HALF_SECOND);
    return 0;
}

/*! mcp_thermocouple_disable() 
 * takes a reference to an active i2c_thermocouple,
 * and disables it, causing it to enter shutdown mode and to no longer be able 
 * to take temperature measurements.
 *
 * @param pdevice is a pointer to an active i2c_thermocouple
 *
 */
int mcp_thermocouple_disable(i2c_thermocouple* pdevice) {
    mcp_close_i2c_bus(pdevice);
    pdevice->filedes = -1;
    pdevice->enabled = 0;
    return 0;
}

/*! mcp_get_temp() 
 * takes an enabled i2c_thermocouple as input, and return the 
 * temperature in celcius. 
 *
 * @see mcp_thermocouple_enable()
 *
 * @param pdevice is a pointer to an active i2c_thermocouple
 *
 * @return float temperature in celcius
 */
float mcp_get_temp(i2c_thermocouple* pdevice) {
  
    if (!pdevice->enabled) {
        fprintf(stderr, ERROR_2);
        return -1;
    }

    char reg[1] = {0x00};
    if (write(pdevice->filedes, reg, 1) < 0) {
        fprintf(stderr, ERROR_6);
        return -1;
    }

    char data[2] = {0};
    if (read(pdevice->filedes, data, 2) != 2) {
        fprintf(stderr, ERROR_4);
        return -1;
    } else {
          if  (data[0] & 0x80) { // if low temp
              return data[0] * 16 + data[1] / 16.0 - 4096;
        } else {
              return data[0] * 16 + data[1] / 16.0;
        }
    }
}

/*! mcp_get_status()
 * test returns the value of the status register of an
 * enabled i2c_thermocouple. This value can give info on the alert
 * registers of the device, as well as other information.
 *
 * @see mcp_thermocouple_enable()
 * 
 * @return char value of status register
 *
 * */
char mcp_get_status(i2c_thermocouple* pdevice) {
    
    if (!pdevice->enabled) {
        fprintf(stderr, ERROR_2);
        return -1;
    }

    char reg[1] = {0};
    reg[0] = 0x04;

    if(write(pdevice->filedes, reg, 1) < 0) {
        fprintf(stderr, ERROR_6);
        return -1;
    }

    char data[1] = {0};

    if(read(pdevice->filedes, data, 1) != 1) {
        fprintf(stderr, ERROR_5);
        return -1;
    }

    return data[0]; 
}


/*! mcp_open_i2c_bus()
 * is a static function not accessible to users 
 * implementing this library. mcp_open_i2c_bus() accesses the i2c bus 
 * (which on linux is "/dev/i2c-<i2c-bus-value>") and initializes it,
 * allowing read-write access to its devices. This function is implemented 
 * in the mcp_thermocouple_enable() function.
 *
 * @see mcp_thermocouple_enable()
 *
 * @param pdevice an i2c_thermocouple pointer
 *
 * @return int error code
 *
 * */
static int mcp_open_i2c_bus(i2c_thermocouple* pdevice) {
    
    if (pdevice->enabled == 1) {
        fprintf(stderr, ERROR_8);
        return -1;
    }
    char* bus = mcp_thermocouple_bus_to_string(pdevice->i2c_bus_int);
    if ((pdevice->filedes = open(bus, O_RDWR)) < 0) {
        fprintf(stderr, ERROR_0);
        return -1;
    }
    
    ioctl(pdevice->filedes, I2C_SLAVE, pdevice->i2c_address);

    MCP_CONFIGURE(pdevice->filedes, THERMOCOUPLE_SENSOR_TYPE_REGISTER, K_TYPE)
    MCP_CONFIGURE(pdevice->filedes, DEVICE_CONFIG_REGISTER, NORMAL_MODE)
    return 0;
}

/*! mcp_close_i2c_bus()
 * is a static function not accessible to users 
 * implementing this library. mcp_close_i2c_bus() accesses the i2c bus 
 * (which on linux is "/dev/i2c-<i2c-bus-value>") and closes it,
 * diabling further read-write access to its devices. This function is 
 * implemented in the mcp_thermocouple_mcp_thermocouple_disable() function.
 *
 * @see mcp_thermocouple_enable()
 *
 * @param pdevice an i2c_thermocouple pointer
 *
 * @return 0 on success
 * @return -1 on failure
 *
 * */
static int mcp_close_i2c_bus(i2c_thermocouple* pdevice) {
    
    MCP_CONFIGURE(pdevice->filedes, DEVICE_CONFIG_REGISTER, SHUTDOWN_MODE)
    if (close(pdevice->filedes) < 0) {
        fprintf(stderr, ERROR_3);
        return -1;
    }
    return 0;
}

/*! mcp_thermocouple_bus_to_string()
 * is a static function not accessible to 
 * users implementing this library. mcp_thermocouple_bus_to_string() converts
 * the integer value passed to the function and returns a file bath to an 
 * i2c bus with that value appended. Effectivly returning a handle to the 
 * desired i2c bus.
 *
 * @see i2c_thermocouple
 *
 * @param pdevice an i2c_thermocouple pointer
 *
 * @return file path to i2c bus on success
 * @return empty string on failure
 *
 */
static char* mcp_thermocouple_bus_to_string(int i2c_bus) {
   if (i2c_bus >= 3 || i2c_bus < 1) {
        return "";
    } else {
        static char buffer[BUFFER_SIZE];
        snprintf(buffer, BUFFER_SIZE, "/dev/i2c-%d", i2c_bus);
        return buffer;
    }
}
