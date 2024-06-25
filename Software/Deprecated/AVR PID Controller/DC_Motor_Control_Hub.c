#define F_CPU 8000000UL

#include "motors.h"
#include "adc.h"
#include "spi.h"
#include "conversions.h"
#include <util/delay.h>

/*
    TO DO: [2 is tested and verified, 1 is complete, 0 is incomplete]
        --- I/O Module ---
        1: Data direction register setup; Designate inputs and outputs.
        1: Analog to digital converted setup; Function that returns ADCx reading. 
        1: Pulse width modulation setup; Function that sets the speeds of the motors.
        --- Protection Module ---
        1: Function that estimates the current draw of EACH motor using the ammeters. (See notebook)
        0: Motor stall detection; Uses the estimated current draw and known stall current.
        -- Control Module ---
        0: Ability to save and read data to and from the EEPROM. Saves PID values, min. max. for potent. conversion, etc. 
        1: Function that converts potentiometer readings into angles, radians or degrees.
        0: PID Control Loop; Attempts to keep the potentiometer reading at the 'set point' by spinning the motor.
        1: SPI input and output interface; A method of communicating with a device which can send commands to change 'set points'
*/

void Process_SPI_Command() {
    uint8_t commandID = SPI_command_buffer[0]; // See spi.h for command list and descriptions
    uint8_t targetID = SPI_command_buffer[1];  // 1st parameter; controller, motor, or potentiometer id.
    // 2nd parameter; float. bytes must be assembled into a value
    uint8_t cmdParamArray[4] = {SPI_command_buffer[2], SPI_command_buffer[3], SPI_command_buffer[4], SPI_command_buffer[5]};
    float cmdParam = 0; // Declare the 2nd parameter and assign a default value to it
    memcpy(&cmdParam, cmdParamArray, 4); // copy the contents of the cmdParamArray (raw bytes) into the memory where the float is located
    switch (commandID) {
        case SPI_CMD_DUMMY_COMMAND:; // This is sent by the master when it does not have another command in queue but is receiving data
            break;
        case SPI_CMD_SET_TARGET_ANGLE:;
            break;
        case SPI_CMD_READ_TARGET_ANGLE:;
            break;
        case SPI_CMD_READ_CURRENT_ANGLE:;
            float angle;
            switch (targetID) {
                case 1:
                    angle = Convert_Rad_to_Deg(Convert_Potentiometer_ADC(Potentiometer_1_Signal));
                    break;
                case 2:
                    angle = Convert_Rad_to_Deg(Convert_Potentiometer_ADC(Potentiometer_2_Signal));
                    break;
                case 3:
                    angle = Convert_Rad_to_Deg(Convert_Potentiometer_ADC(Potentiometer_3_Signal));
                    break;
                case 4:
                    angle = Convert_Rad_to_Deg(Convert_Potentiometer_ADC(Potentiometer_4_Signal));
                    break;
                default: // Invalid target id
                    angle = -90.0f;
                    break;
            }
            memcpy(SPI_response_buffer, &angle, 4); // The next time SPI_Slave_Transmit is called it will begin sending this data
            break;
        case SPI_CMD_SET_PID_ENABLE:;
            break;
        case SPI_CMD_PID_SET_P:;
            break;
        case SPI_CMD_PID_READ_P:;
            break;
        case SPI_CMD_PID_SET_I:;
            break;
        case SPI_CMD_PID_READ_I:;
            break;
        case SPI_CMD_PID_SET_D:;
            break;
        case SPI_CMD_PID_READ_D:;
            break;
        case SPI_CMD_PID_AUTOTUNE:;
            break;
        case SPI_CMD_READ_CURRENT_DRAW:;
            float current;
            switch (targetID) {
                case 1:
                    current = Convert_Ammeter_Motor(Ammeter_1_Reading, 0.5f/*Motor_1_Speed*/, 0.5f/*Motor_2_Speed*/);
                    break;
                case 2:
                    current = Convert_Ammeter_Motor(Ammeter_1_Reading, 0.5f/*Motor_2_Speed*/, 0.5f/*Motor_1_Speed*/);
                    break;
                case 3:
                    current = Convert_Ammeter_Motor(Ammeter_2_Reading, 0.5f/*Motor_3_Speed*/, 0.5f/*Motor_4_Speed*/);
                    break;
                case 4:
                    current = Convert_Ammeter_Motor(Ammeter_2_Reading, 0.5f/*Motor_4_Speed*/, 0.5f/*Motor_3_Speed*/);
                    break;
                default: // Invalid target id
                    current = -10.0f;
                    break;
            }
            memcpy(SPI_response_buffer, &current, 4);
            break;
        case SPI_CMD_SAVE_SETTINGS:;
            break;
        case SPI_CMD_LOAD_SETTINGS:;
            break;
        case SPI_CMD_SET_MOTOR_SPEED:;
            switch (targetID) {
                case 1:
                    Set_Motor_1_Speed(cmdParam);
                    break;
                case 2:
                    Set_Motor_2_Speed(cmdParam);
                    break;
                case 3:
                    Set_Motor_3_Speed(cmdParam);
                    break;
                case 4:
                    Set_Motor_4_Speed(cmdParam);
                    break;
                default: // Invalid target id
                    break;
            }
            break;
        default /* Unknown CommandID */:;
            break;
    }
}

// SPI Transfer Complete interrupt
ISR(SPI_STC_vect) { // The way this is setup requires master to send something back
                    // so the master should send SPI_CMD_DUMMY_COMMAND in order to 
                    // allow the slave to continue its response.
    uint8_t receiveStatus = SPI_Slave_Receive();
    uint8_t sendStatus = SPI_Slave_Transmit();
    if (receiveStatus == 1)
        Process_SPI_Command();
}

/*
    For the purpose of testing freshly assembled PCBs, this code will only flash the debug LED.
    JP3 Header may be required for programming virgin MCUs.
*/
    
int main(void) {
    Initialize_IO();
    Initialize_ADC();
    Initialize_SPI();
    sei(); // Enable global interrupts

    Set_Motor_1_Speed(0.5f);
    Set_Motor_2_Speed(-1.0f);
    Set_Motor_3_Speed(0.75f);
    Set_Motor_4_Speed(0.0f);

    // Call the read_xxxxx functions once per 'frame'
    uint16_t p1_sig = Read_Potentiometer_1();
    uint16_t p2_sig = Read_Potentiometer_2();
    uint16_t p3_sig = Read_Potentiometer_3();
    uint16_t p4_sig = Read_Potentiometer_4();

    uint16_t a1_reading = Read_Ammeter_1();
    uint16_t a2_reading = Read_Ammeter_2();

    DDRC |= (1 << Debug_LED);
    while (1) {
        PORTC ^= (1 << Debug_LED); // Flip the bit that corresponds to the debug led on port c
        _delay_ms(250); // wait 250 milliseconds (1/4 seconds)
    }

    return 0;
}