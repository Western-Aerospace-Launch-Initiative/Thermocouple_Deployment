module PEP_GS_Main {

    @Port for requesting temperature 
    port ThermocoupleID(
                       id_string: string size 20 @< The ID of the termocouple wanted to measure
                       )

    @Port for returning enabled stat
    port Enabled(
                enabled: bool @< The boolean value saying if the device is enabled or not 
                )

    @Port for returning temperature
    port Temperature(
                    result: F32 @< The returned temperature value
                    )

    @Port for returning status register value
    port Status(
                statusID: U8 @< The returned status register value
             )

}
