#ifndef __AVR_ATmega328P__ 
    #define __AVR_ATmega328P__
#endif
#ifndef _SPI_H_
    #define _SPI_H_
    #define MAX_SPI_BUFFER_LENGTH 6    // Max number of characters per command

    #include <avr/interrupt.h>
    #include <string.h>

    // Serial Peripheral Interface pins; some pins do not have their data direction overriden automatically so we must set those up too.
    #define MISO                4       // PORTB - PIN 4 - Master In Slave Out - DDR User Defined in slave mode
    #define MOSI                3       // PORTB - PIN 3 - Master Out Slave In - Auto override to input in slave mode
    #define SS                  2       // PORTB - PIN 2 - Slave select (Inverted) - Auto override to input in slave mode
    #define SCK                 5       // PORTB - PIN 5 - Source Clock - Auto override to input in slave mode
    // The MCUs on the DC Motor Control Hub PCB will operate in slave mode

    // SPI COMMANDS
    #define SPI_CMD_DUMMY_COMMAND               0x00        // Command ID: 0; Empty command that does nothing.
                                                                // Sent by master to tell slave to continue its tranmission.
    #define SPI_CMD_SET_TARGET_ANGLE            0x01        // Command ID: 1; Sets target angle for PID controller.
                                                                // Param: uint8_t controllerID, float angle
    #define SPI_CMD_READ_TARGET_ANGLE           0x02        // Command ID: 2; Returns the set angle for the specified PID controller.
                                                                // Param: uint8_t controllerID
    #define SPI_CMD_READ_CURRENT_ANGLE          0x03        // Command ID: 3; Returns the angle reading from the specified potentiometer.
                                                                // Param: uint8_t potentiometerID
    #define SPI_CMD_SET_PID_ENABLE              0x04        // Command ID: 4; Enables or disables the specified PID controller.
                                                                // Param: uint8_t controllerID, uint8_t enabled (0 = disabled)
    #define SPI_CMD_PID_SET_P                   0x05        // Command ID: 5; Sets the 'proportional' component of the PID controller.
                                                                // Param: uint8_t controllerID, float proportional
    #define SPI_CMD_PID_READ_P                  0x06        // Command ID: 6; Returns the 'proportional' component of the PID controller.
                                                                // Param: uint8_t controllerID
    #define SPI_CMD_PID_SET_I                   0x07        // Command ID: 7; Sets the 'integral' component of the PID controller.
                                                                // Param: uint8_t controllerID, float integral   
    #define SPI_CMD_PID_READ_I                  0x08        // Command ID: 8; Returns the 'integral' component of the PID controller.
                                                                // Param: uint8_t controllerID                                                         
    #define SPI_CMD_PID_SET_D                   0x09        // Command ID: 9; Sets the 'derivative' component of the PID controller.
                                                                // Param: uint8_t controllerID, float derivative
    #define SPI_CMD_PID_READ_D                  0x0a        // Command ID: 10; Returns the 'derivative' component of the PID controller.
                                                                // Param: uint8_t controllerID
    #define SPI_CMD_PID_AUTOTUNE                0x0b        // Command ID: 11; Runs the auto-tune algorithm for specified PID controller.
                                                                // Param: uint8_t controllerID
    #define SPI_CMD_READ_CURRENT_DRAW           0x0c        // Command ID: 12; Returns the estimated current draw of the specified motor.
                                                                // Param: uint8_t motorID
    #define SPI_CMD_SAVE_SETTINGS               0x0d        // Command ID: 13; Saves the current PID values to the EEPROM
                                                                // No parameters
    #define SPI_CMD_LOAD_SETTINGS               0x0e        // Command ID: 14; Loads the PID settings from the EEPROM
                                                                // No parameters
    #define SPI_CMD_SET_MOTOR_SPEED             0x0f        // Command ID: 15; Overrides the motor speed, disable PIDs to use this command.
                                                                // Param: uint8_t motorID, float speed

    // SPI Command Structure
    // Byte 0: [Command ID], Byte 1: [Target ID], Byte 2: [float_byte_1], Byte 3: [float_byte_2], Byte 4: [float_byte_3], Byte 5: [float_byte_4]
    // SPI Response Structure
    // Byte 0: [float_byte_1], Byte 1: [float_byte_2], Byte 2: [float_byte_3], Byte 3: [float_byte_4], Byte 4: [Empty], Byte 5: [Empty]

    /*
        Sets the data direction registers for the MOSI pin and enables SPI in slave mode.
        You'll want to change this to enable with interrupts and setup a receive char[] function for when a command is send to one of these 
        controllers. 
    */
    void Initialize_SPI(void);

    /*
        Function used by the SPI interrupt vector: SPI_STC_vect to receive a byte

        @return tranmissionComplete: Returns 0 if receiving anything and return 1 when the receive buffer overflows.
    */
    uint8_t SPI_Slave_Receive(void);

    /*
        Transmits the byte in the SPI response buffer that is pointed to by the SPI response index and then increments it.

        @return tranmissionComplete: Returns 0 if transmitting anything and returns 1 when the send buffer overflows.
    */
    uint8_t SPI_Slave_Transmit(void);

    /*
        Global character buffer containing the most recent SPI command
    */
    static uint8_t SPI_command_buffer[MAX_SPI_BUFFER_LENGTH] = {
        SPI_CMD_DUMMY_COMMAND,
        SPI_CMD_DUMMY_COMMAND,
        SPI_CMD_DUMMY_COMMAND,
        SPI_CMD_DUMMY_COMMAND,
        SPI_CMD_DUMMY_COMMAND,
        SPI_CMD_DUMMY_COMMAND
    };

    /*
        Global index pointing to location in the SPI command buffer that is being written to
    */
    static uint8_t SPI_command_index = 0;

    /*
        Global character buffer containing the most recent SPI response
    */
    static uint8_t SPI_response_buffer[MAX_SPI_BUFFER_LENGTH] = {
        SPI_CMD_DUMMY_COMMAND,
        SPI_CMD_DUMMY_COMMAND,
        SPI_CMD_DUMMY_COMMAND,
        SPI_CMD_DUMMY_COMMAND,
        SPI_CMD_DUMMY_COMMAND,
        SPI_CMD_DUMMY_COMMAND
    };

    /*
        Global index pointing to location in the SPI response buffer that is being written to
    */
    static uint8_t SPI_response_index = 0;

    /*
        Writes SPI_CMD_DUMMY_COMMAND to entire command buffer and returns the command index to 0.
    */
    void ClearCommandBuffer(void);

    /*
        Writes SPI_CMD_DUMMY_COMMAND to entire response buffer and returns the response index to 0.
    */
    void ClearResponseBuffer(void);
#endif