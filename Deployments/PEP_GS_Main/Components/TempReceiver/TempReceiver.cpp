// ======================================================================
// \title  TempReceiver.cpp
// \author noahbraasch
// \brief  cpp file for TempReceiver component implementation class
// ======================================================================


#include <PEP_GS_Main/Components/TempReceiver/TempReceiver.hpp>
#include <FpConfig.hpp>
#include "MCP9600.h"
namespace PEP_GS_Main {

  // ----------------------------------------------------------------------
  // Construction, initialization, and destruction
  // ----------------------------------------------------------------------

  TempReceiver ::
    TempReceiver(
        const char *const compName
    ) : TempReceiverComponentBase(compName)
  {
    
  }

  TempReceiver ::
    ~TempReceiver()
  {

  }

  // ----------------------------------------------------------------------
  // Handler implementations for user-defined typed input ports
  // ----------------------------------------------------------------------

  void TempReceiver ::
    thermocoupleIdIn_handler(
        const NATIVE_INT_TYPE portNum,
        const id_stringString &id_string
    )
  {
    i2c_thermocouple* device;
    //device.i2c_bus_int = 2; /*!< an integer that stores the i2c bus*/
    //device.i2c_address = 0x60; /*!< an integer that stores the i2c address*/
    //device.filedes = -1; /*!< an integer that stores the file designator */
    //device.thermocouple_type = K_TYPE; /*!< a char that stores the thermocouple type*/
    //device.enabled = 0;/*!< a char that stores the enabled status*/ 
    /*!< a string that stores the device ID*/ 
    device = mcp_thermocouple_init(2, 0x60, K_TYPE, "Test");
    mcp_thermocouple_enable(device); 
    F32 temp = mcp_get_temp(device);
    U8 status = device->i2c_address;
    this->EnabledOut_out(0, 1);
    this->TempOut_out(0, temp);
    this->statusOut_out(0, status); 
    mcp_thermocouple_disable(device);
  }

  // ----------------------------------------------------------------------
  // Command handler implementations
  // ----------------------------------------------------------------------

  void TempReceiver ::
    TODO_cmdHandler(
        const FwOpcodeType opCode,
        const U32 cmdSeq
    )
  {
    // TODO
    this->cmdResponse_out(opCode,cmdSeq,Fw::CmdResponse::OK);
  }

} // end namespace PEP_GS_Main
