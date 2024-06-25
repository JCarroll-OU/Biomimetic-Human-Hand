#include "motors.h"

void Initialize_IO(void) {
    // 1 is output, 0 is input. By default, pins are set to input.

    // Set the data direction register for port b
    DDRB |= (1 << Motor_1_Enable);                      // Set OC1A to output
    DDRB |= (1 << Motor_3B);                            // Set PB3 to output
    DDRB |= (1 << Motor_4A);                            // Set PB6 to output
    DDRB |= (1 << Motor_4B);                            // Set PB7 to output

    // Set the data direction register for port c
    DDRC |= (1 << Debug_LED);                           // Set PC4 to output

    // Set the data direction register for port d
    DDRD |= (1 << Motor_3A);                            // Set PD0 to output
    DDRD |= (1 << Motor_2B);                            // Set PD1 to output
    DDRD |= (1 << Motor_2A);                            // Set PD2 to output
    DDRD |= (1 << Motor_2_Enable);                      // Set OC2B to output
    DDRD |= (1 << Motor_1B);                            // Set PD4 to output
    DDRD |= (1 << Motor_3_Enable);                      // Set OC0B to output
    DDRD |= (1 << Motor_4_Enable);                      // Set OC0A to output
    DDRD |= (1 << Motor_1A);                            // Set PD7 to output

    // Initialize pulse width modulation for PB1, Motor_1_Enable
    OCR1A = DEFAULT_PWM_DUTY_CYCLE;                     // Set duty-cycle to default
    TCCR1A |= (1 << COM1A1);                            // Set non-inverting mode
    TCCR1A |= (0 << WGM11) | (1 << WGM10);              // Set to 8-bit phase correct mode (to use 10-bit, change 0<<WGM11 to 1<<WGM11)
    TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10);  // Set pre-scaler to 1/8, 8Mhz MCU -> 1Mhz ADC

    // Initialize pulse width modulation for PD3, Motor_2_Enable
    OCR2B = DEFAULT_PWM_DUTY_CYCLE;                     // Set duty-cycle to default
    TCCR2A |= (1 << COM2A1);                            // Set non-inverting mode
    TCCR2A |= (0 << WGM21) | (1 << WGM20);              // Set to 8-bit phase correct mode (8-bit is max for this timer)
    TCCR2B |= (0 << CS22) | (1 << CS21) | (0 << CS20);  // Set pre-scaler to 1/8, 8Mhz MCU -> 1Mhz ADC 

    // Initialize pulse modulation for PD5 and PD6, Motor_3_Enable and Motor_4_Enable
    OCR0A = DEFAULT_PWM_DUTY_CYCLE;                     // Set duty-cycle to default, Motor_4_Enable
    OCR0B = DEFAULT_PWM_DUTY_CYCLE;                     // Set duty-cycle to default, Motor_3_Enable
    TCCR0A |= (1 << COM0A1);                            // Set non-inverting mode
    TCCR0A |= (0 << WGM01) | (1 << WGM00);              // Set to 8-bit phase correct mode (8-bit is max for this timer)
    TCCR0B |= (0 << CS02) | (1 << CS01) | (0 << CS00);  // Set pre-scaler to 1/8, 8Mhz MCU -> 1Mhz ADC 
}

void Set_Motor_1_Speed(float spd) {
    // Set the speed of motor 1 by altering the PWM duty cycle
    uint8_t duty_cycle = (uint8_t)(fabs(spd) * 0xFF);
    OCR1A = duty_cycle;

    // Set the direction of motor 1
    if (spd > 0) {                      // Motor should spin forwards
        PORTD |= (1 << Motor_1A);       // Set Motor_1A to high
        PORTD &= ~(1 << Motor_1B);      // Set Motor_1B to low
    } else if (spd < 0) {               // Motor should spin backwards
        PORTD &= ~(1 << Motor_1A);      // Set Motor_1A to low
        PORTD |= (1 << Motor_1B);       // Set Motor_1B to high
    } else {                            // Motor should not spin 
        PORTD &= ~(1 << Motor_1A);      // Set Motor_1A to low
        PORTD &= ~(1 << Motor_1B);      // Set Motor_1B to low
    }
}

void Set_Motor_2_Speed(float spd) {
    // Set the speed of motor 2 by altering the PWM duty cycle
    uint8_t duty_cycle = (uint8_t)(fabs(spd) * 0xFF);
    OCR2B = duty_cycle;

    // Set the direction of motor 2
    if (spd > 0) {                      // Motor should spin forwards
        PORTD |= (1 << Motor_2A);       // Set Motor_2A to high
        PORTD &= ~(1 << Motor_2B);      // Set Motor_2B to low
    } else if (spd < 0) {               // Motor should spin backwards
        PORTD &= ~(1 << Motor_2A);      // Set Motor_2A to low
        PORTD |= (1 << Motor_2B);       // Set Motor_2B to high
    } else {                            // Motor should not spin
        PORTD &= ~(1 << Motor_2A);      // Set Motor_2A to low
        PORTD &= ~(1 << Motor_2B);      // Set Motor_2B to low
    }
}

void Set_Motor_3_Speed(float spd) {
    // Set the speed of motor 3 by altering the PWM duty cycle
    uint8_t duty_cycle = (uint8_t)(fabs(spd) * 0xFF);
    OCR0B = duty_cycle;

    // Set the direction of motor 3
    if (spd > 0) {                      // Motor should spin forwards
        PORTD |= (1 << Motor_3A);       // Set Motor_3A to high
        PORTB &= ~(1 << Motor_3B);      // Set Motor_3B to low
    } else if (spd < 0) {               // Motor should spin backwards
        PORTD &= ~(1 << Motor_3A);      // Set Motor_3A to low
        PORTB |= (1 << Motor_3B);       // Set Motor_3B to high
    } else {                            // Motor should not spin
        PORTD &= ~(1 << Motor_3A);      // Set Motor_3A to low
        PORTB &= ~(1 << Motor_3B);      // Set Motor_3B to low
    }
}

void Set_Motor_4_Speed(float spd) {
    // Set the speed of motor 4 by altering the PWM duty cycle
    uint8_t duty_cycle = (uint8_t)(fabs(spd) * 0xFF);
    OCR0A = duty_cycle;

    // Set the direction of motor 4
    if (spd > 0) {                      // Motor should spin forwards
        PORTB |= (1 << Motor_4A);       // Set Motor_4A to high
        PORTB &= ~(1 << Motor_4B);      // Set Motor_4B to low
    } else if (spd < 0) {               // Motor should spin backwards
        PORTB &= ~(1 << Motor_4A);      // Set Motor_4A to low
        PORTB |= (1 << Motor_4B);       // Set Motor_4B to high
    } else {                            // Motor should not spin
        PORTB &= ~(1 << Motor_4A);      // Set Motor_4A to low
        PORTB &= ~(1 << Motor_4B);      // Set Motor_4B to low
    }
}