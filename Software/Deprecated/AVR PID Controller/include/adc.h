#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#ifndef _ADC_H_
    #define _ADC_H_

    #include <avr/io.h>

    #define Pot_1_Signal        0       // ADC0 - Analog input - Used to measure the angle of the joint driven by motor 1.
    #define Pot_2_Signal        1       // ADC1 - Analog input - Used to measure the angle of the joint driven by motor 2.
    #define Pot_3_Signal        2       // ADC2 - Analog input - Used to measure the angle of the joint driven by motor 3.
    #define Pot_4_Signal        3       // ADC3 - Analog input - Used to measure the angle of the joint driven by motor 4.

    #define Ammeter_1           6       // ADC6 - Analog input - Used to measure current draw for the first motor controller.
    #define Ammeter_2           7       // ADC7 - Analog input - Used to measure current draw for the second motor controller.

    /*
        Sets voltage reference and pre-scalar, then enables the ADC.
    */
    void Initialize_ADC(void);

    /*
        Starts an analog to digital conversion and waits for the result, then returns it.
        
        @param uint8_t channel: Channel to set the ADC to. 

        @return Value from ADC channel.
    */
    uint16_t ADC_Convert(uint8_t channel);

    /*
        Updates the 'Potentiometer_1_Signal' value using ADC_Convert and returns it. 

        @return Potentiometer_1_Signal: Result from ADC conversion 
    */
    uint16_t Read_Potentiometer_1(void);

    /*
        Updates the 'Potentiometer_2_Signal' value using ADC_Convert and returns it. 

        @return Potentiometer_2_Signal: Result from ADC conversion 
    */
    uint16_t Read_Potentiometer_2(void);

    /*
        Updates the 'Potentiometer_3_Signal' value using ADC_Convert and returns it. 

        @return Potentiometer_3_Signal: Result from ADC conversion 
    */
    uint16_t Read_Potentiometer_3(void);

    /*
        Updates the 'Potentiometer_4_Signal' value using ADC_Convert and returns it. 

        @return Potentiometer_4_Signal: Result from ADC conversion 
    */
    uint16_t Read_Potentiometer_4(void);

    /*
        Updates the 'Ammeter_1_Reading' value using ADC_Convert and returns it.

        @return Ammeter_1_Reading: Result from ADC conversion
    */
    uint16_t Read_Ammeter_1(void);

    /*
        Updates the 'Ammeter_2_Reading' value using ADC_Convert and returns it.

        @return Ammeter_2_Reading: Result from ADC conversion
    */
    uint16_t Read_Ammeter_2(void);

    static uint16_t Potentiometer_1_Signal, Potentiometer_2_Signal, Potentiometer_3_Signal, Potentiometer_4_Signal;
    static uint16_t Ammeter_1_Reading, Ammeter_2_Reading;
#endif