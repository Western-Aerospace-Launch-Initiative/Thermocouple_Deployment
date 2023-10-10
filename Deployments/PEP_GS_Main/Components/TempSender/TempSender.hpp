// ======================================================================
// \title  TempSender.hpp
// \author noahbraasch
// \brief  hpp file for TempSender component implementation class
// ======================================================================

#ifndef TempSender_HPP
#define TempSender_HPP

#include "PEP_GS_Main/Components/TempSender/TempSenderComponentAc.hpp"

namespace PEP_GS_Main {

  class TempSender :
    public TempSenderComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object TempSender
      //!
      TempSender(
          const char *const compName /*!< The component name*/
      );

      //! Destroy object TempSender
      //!
      ~TempSender();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for EnabledIn
      //!
      void EnabledIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          bool enabled /*!< 
      The boolean value saying if the device is enabled or not
      */
      );

      //! Handler implementation for TempIn
      //!
      void TempIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          F32 result /*!< 
      The returned temperature value
      */
      );

      //! Handler implementation for statusIn
      //!
      void statusIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          U8 statusID /*!< 
      The returned status register value
      */
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for ENABLE_THERMOCOUPLE command handler
      //! Command for enabling and initializing thermocouples
      void ENABLE_THERMOCOUPLE_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          const Fw::CmdStringArg& identifier /*!< 
          Identifier for the thermocouple
          */
      );

      //! Implementation for DISABLE_THERMOCOUPLE command handler
      //! 
      void DISABLE_THERMOCOUPLE_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          const Fw::CmdStringArg& identifier /*!< 
          Identifier for the thermocouple
          */
      );

      //! Implementation for GET_TEMPERATURE command handler
      //! 
      void GET_TEMPERATURE_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          const Fw::CmdStringArg& identifier /*!< 
          Identifier for the thermocouple
          */
      );

      //! Implementation for GET_STATUS command handler
      //! 
      void GET_STATUS_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq, /*!< The command sequence number*/
          const Fw::CmdStringArg& identifier /*!< 
          Identifier for the thermocouple
          */
      );


    };

} // end namespace PEP_GS_Main

#endif
