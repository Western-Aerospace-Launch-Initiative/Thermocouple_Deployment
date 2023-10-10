module PEP_GS_Main {
    
    @ Component for sending temperature commands from gds
    active component TempSender {


        # General Ports

        @ Port for sending thermocouple ID
        output port thermocoupleIdOut: ThermocoupleID 

        @ Port for receiving enabled value
        async input port EnabledIn: Enabled 

        @ Port for receiving temperature
        async input port TempIn: Temperature

        @ Port for receiving status codes
        async input port statusIn: Status 
            

        # Commands

        @ Command for enabling and initializing thermocouples
        async command ENABLE_THERMOCOUPLE(
            identifier: string size 20 @< Identifier for the thermocouple
        )

        async command DISABLE_THERMOCOUPLE(
            identifier: string size 20 @< Identifier for the thermocouple
        )

        async command GET_TEMPERATURE(
            identifier: string size 20 @< Identifier for the thermocouple
        )

        async command GET_STATUS(
            identifier: string size 20 @< Identifier for the thermocouple
        )


        # Events

        @ Event confirming enable for a thermocouple
        event THERMOCOUPLE_ENABLED(
            enable_success: string size 20 @< Success string of the command
        ) severity activity low format "Thermocouple {} has been enabled."

        event THERMOCOUPLE_DISABLED(
            disable_success: string size 20 @< Success string of command
        ) severity activity high format "Thermocouple {} has been disabled."

        event TEMP_RECEIVED(
            ID: string size 20 @< The ID of the sender themocouple
            temp: F32 @< The temperature value sent
        ) severity activity high format "Thermocouple {} is measuring {} degrees celcius."

        event STATUS_RECEIVED(
            ID: string size 20 @< The ID of the sender thermocouple
            status: U8 @< The status code of the thermocouple
        ) severity activity high format "Thermocouple {} is returning status code: {}."


        # Telemetry

        @ Telemetry channel for viewing current state of thermocouple
        telemetry ENABLED: bool

        @ Telemetry channel for viewing current temperature
        telemetry TEMPERATURE: F32

        @ Telemetry channel for seeing status code register
        telemetry STATUS: U8
       




        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending command registrations
        command reg port cmdRegOut

        @ Port for receiving commands
        command recv port cmdIn

        @ Port for sending command responses
        command resp port cmdResponseOut

        @ Port for sending textual representation of events
        text event port logTextOut

        @ Port for sending events to downlink
        event port logOut

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

    }
}
