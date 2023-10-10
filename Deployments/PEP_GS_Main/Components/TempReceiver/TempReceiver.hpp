// ======================================================================
// \title  TempReceiver.hpp
// \author noahbraasch
// \brief  hpp file for TempReceiver component implementation class
// ======================================================================

#ifndef TempReceiver_HPP
#define TempReceiver_HPP

#include "PEP_GS_Main/Components/TempReceiver/TempReceiverComponentAc.hpp"

namespace PEP_GS_Main {

  class TempReceiver :
    public TempReceiverComponentBase
  {

    public:

      // ----------------------------------------------------------------------
      // Construction, initialization, and destruction
      // ----------------------------------------------------------------------

      //! Construct object TempReceiver
      //!
      TempReceiver(
          const char *const compName /*!< The component name*/
      );

      //! Destroy object TempReceiver
      //!
      ~TempReceiver();

    PRIVATE:

      // ----------------------------------------------------------------------
      // Handler implementations for user-defined typed input ports
      // ----------------------------------------------------------------------

      //! Handler implementation for thermocoupleIdIn
      //!
      void thermocoupleIdIn_handler(
          const NATIVE_INT_TYPE portNum, /*!< The port number*/
          const id_stringString &id_string /*!< 
      The ID of the termocouple wanted to measure
      */
      );

    PRIVATE:

      // ----------------------------------------------------------------------
      // Command handler implementations
      // ----------------------------------------------------------------------

      //! Implementation for TODO command handler
      //! TODO
      void TODO_cmdHandler(
          const FwOpcodeType opCode, /*!< The opcode*/
          const U32 cmdSeq /*!< The command sequence number*/
      );


    };

} // end namespace PEP_GS_Main

#endif
