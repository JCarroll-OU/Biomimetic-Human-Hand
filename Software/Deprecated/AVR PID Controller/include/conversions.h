#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#ifndef _CONVERSIONS_H_
    #define _CONVERSIONS_H_
    #define AMMETER_SHUNT_RESISTOR_VALUE 0.1 // Ohms
    #include <avr/io.h>
    #include <math.h>

    /*
        Converts ADC readings from the 'ammeters' to mA.

        @param uint16_t ammeterReading: Output from the ADC that corresponds to the ammeter input.

        @return float: Current draw in milli-amps.
    */
    float Convert_Ammeter_ADC(uint16_t ammeterReading);

    /*
        Converts ammeter mA readings into estimated current draw for the motor corresponding to speed 1.

        @param float ammeterReading: Output from the Convert_Ammeter_ADC function.

        @param float spd1: Speed of motor 1, this is the motor that the function is estimating the current draw of. 

        @param float spd2: Speed of motor 2, this is the speed of the other motor connected to the driver that corresponds
                            to the ammeter reading.

        @return estimate: Estimated current draw of the motor corresponding to spd1.
    */
    float Convert_Ammeter_Motor(float ammeterReading, float spd1, float spd2);

    /*
        Converts ADC readings from the potentiometers to radians.

        @param uint16_t potReading: Output from the ADC that corresponds to the potentiometer input.

        @return float: Angle from potentiometer in radians.
    */
    float Convert_Potentiometer_ADC(uint16_t potReading);

    /*
        Converts input from radians to degrees.

        @param float rad: Measure in radians.

        @return float: Measure in degrees.
    */
    float Convert_Rad_to_Deg(float rad);

    /*
        Converts input from degrees to radians.

        @param float deg: Measure in degrees.

        @return float: Measure in radians.
    */
    float Convert_Deg_to_Rad(float deg);
#endif