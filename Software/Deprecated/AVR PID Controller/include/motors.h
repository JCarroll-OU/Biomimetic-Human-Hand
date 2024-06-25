#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#ifndef _MOTORS_H_
    #define _MOTORS_H_
    #define DEFAULT_PWM_DUTY_CYCLE 128  // All PWM Timer/Counters operate in 8-bit phase correct mode

    #include <avr/io.h>
    #include <math.h>

    #define Motor_1_Enable      1       // PORTB - PIN 1 - OC1A - PWM output - Controls speed of motor 1.
    #define Motor_1A            7       // PORTD - PIN 7 - Digital output - Used with 1B to control direction & braking.
    #define Motor_1B            4       // PORTD - PIN 4 - Digital output - Used with 1A to control direction & braking.

    #define Motor_2_Enable      3       // PORTD - PIN 3 - OC2B - PWM output - Controls speed of motor 2.
    #define Motor_2A            2       // PORTD - PIN 2 - Digital output - Used with 2B to control direction & braking.
    #define Motor_2B            1       // PORTD - PIN 1 - Digital output - Used with 2A to control direction & braking.

    #define Motor_3_Enable      5       // PORTD - PIN 5 - OC0B - PWM output - Controls speed of motor 3.
    #define Motor_3A            0       // PORTD - PIN 0 - Digital output - Used with 3B to control direction & braking.
    #define Motor_3B            3       // PORTB - PIN 3 - Digital output - Used with 3A to control direction & braking.

    #define Motor_4_Enable      6       // PORTD - PIN 6 - OC0A - PWM output - Controls speed of motor 4.
    #define Motor_4A            6       // PORTB - PIN 6 - Digital output - Used with 3B to control direction & braking.
    #define Motor_4B            0       // PORTB - PIN 0 - Digital output - Used with 3A to control direction & braking.

    #define Debug_LED           4       // PORTC - PIN 4 / ADC4 - Digital output

    /*
        Sets necessary ports to output and enables pulse width modulation in 8-bit phase correct mode with 1/8 pre-scalar.
    */
    void Initialize_IO(void);

    /*
        Sets the speed and direction of motor 1 based on the sign and magnitude of the speed parameter.

        @param float speed: [-1, 1] Motors stop (brake) at 0 and negative numbers spin the motor in the opposite direction. 
    */
    void Set_Motor_1_Speed(float speed);

    /*
        Sets the speed and direction of motor 2 based on the sign and magnitude of the speed parameter.

        @param float speed: [-1, 1] Motors stop (brake) at 0 and negative numbers spin the motor in the opposite direction. 
    */
    void Set_Motor_2_Speed(float speed);

    /*
        Sets the speed and direction of motor 3 based on the sign and magnitude of the speed parameter.

        @param float speed: [-1, 1] Motors stop (brake) at 0 and negative numbers spin the motor in the opposite direction. 
    */
    void Set_Motor_3_Speed(float speed);

    /*
        Sets the speed and direction of motor 4 based on the sign and magnitude of the speed parameter.

        @param float speed: [-1, 1] Motors stop (brake) at 0 and negative numbers spin the motor in the opposite direction. 
    */
    void Set_Motor_4_Speed(float speed);
#endif