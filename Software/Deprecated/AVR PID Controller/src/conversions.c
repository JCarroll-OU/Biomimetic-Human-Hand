#include "conversions.h"

/*
    The INA180A's are powered by 5v and monitor the voltage drop across the shunt resistor which is connected
    to 12v. The L293D's are also powered by 5v (for the internal logic) and use 12v to power the motors. This 
    means that the current reading given by these ammeters represents the power draw of only the motors, but 
    both motors combined. Using the speeds of the motors, the current draw of each motor can be estimated.
*/
float Convert_Ammeter_ADC(uint16_t ammeterReading) {
    float ammeterVoltage = ((float)ammeterReading / 1024.0f) * 5.0f; // Convert ADC signal into a voltage, 5v = max
    return ammeterVoltage / (20 * AMMETER_SHUNT_RESISTOR_VALUE);
}

/*
         Speed 1
    ----------------- * Current [mA] ~= Current Draw of motor corresponding to speed 1 [mA]
    Speed 1 + Speed 2
    fabs = absolute value for floats, we only care about the magnitude, not direction
*/
float Convert_Ammeter_Motor(float ammeterReading, float spd1, float spd2) {
    return ammeterReading * (fabs(spd1) / (fabs(spd1) + fabs(spd2)));
}

/*
    The potentiometers are connected to 5V, ADCx, and GND.
    They have a maximum resistance of 1k. According to tests with an arduino nano, the
    values at the extremes of the potentiometer's range of motion are about 0 and 1023 
    for 0 and 180 degrees respectively. This will need to be redone using the correct
    hardware: AtMega328p and 8x DC Motor Control Hub Mk. 3
    For now, this should give you an idea of what the function should look like, the
    values are just subject to change. This function converts to degrees!
*/
float Convert_Potentiometer_ADC(uint16_t potReading) {
    return ((float)potReading / 1024.0f) * 1.5708f; // 1.5707 ~= pi/2
}

float Convert_Rad_to_Deg(float rad) {
    return rad * 57.2958f;
}

float Convert_Deg_to_Rad(float deg) {
    return deg * 0.0174533f;
}