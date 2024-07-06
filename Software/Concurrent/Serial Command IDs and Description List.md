# Serial Command IDs and descriptions list
  0. SERIAL_CMD_EMPTY
     - Used as part of the handshake protocal. Returns elasped runtime in seconds.
     - Accepts no parameters.
       - Target ID: N/A
       - Param: N/A
     - Example usage:
       - Host: "1 0 0 0.0\n"
         - Controller 1, Command 0, PID 0, 0.0 
       - Client: "13.86\n"
         - Elasped time: 13.86s

  1. SERIAL_CMD_SET_TARGET_ANGLE
     - Sets the 'target angle' variable for the specified PID controller. This is the angle (in degrees) that the PID controller will attempt to move to and hold. 
     - Accepts all parameters
        - Target ID: [1, 4] Int. Values {1, 2, 3, or 4}
          - PID controller to set the target angle of.
        - Param: float [Joint_Range_Min, Joint_Range_Max]
          - New value for the target angle.
     - Example usage:
        - Host: "1 1 2 36.28\n"
          - Controller 1, Command 1, PID 2, 36.28 degrees 
        - Client: "Done\n"

  2. SERIAL_CMD_GET_TARGET_ANGLE
     - Returns the target angle variable for the specified PID controller. 
     - Accepts only the target ID parameter.
        - Target ID: [1, 4] Int. Values {1, 2, 3, or 4}
          - PID controller to get the target angle from.
        - Param: N/A
     - Example usage:
        - Host: "1 2 2 0.0\n"
          - Controller 1, Command 2, PID 2, 0.0 
        - Client: "36.28\n"
          - Target angle: 36.28 degrees

  3. SERIAL_CMD_GET_CURRENT_ANGLE
     - Returns the potentiometer reading (converted to degrees) associated with the specified PID controller.
     - Accepts only the target ID parameter.
        - Target ID: [1, 4] Int. Values {1, 2, 3, or 4}
          - PID controller to get the target angle from.
        - Param: N/A
     - Example usage:
        - Host: "1 3 1 0.0\n"
          - Controller 1, Command 3, PID 1, 0.0 
        - Client: "28.45\n"
          - Current angle: 28.45 degrees

  4. SERIAL_CMD_SET_PID_ENABLE
     - Enables or disables the specified PID controller. Disabling the controller is necessary when manually overriding the motor speed.
     - Accepts all parameters
        - Target ID: [1, 4] Int. Values {1, 2, 3, or 4}
          - PID controller to enable/disable.
        - Param: float, no min/max
          - PID enable state. bool (Param != 0).
     - Example usage:
        - Host: "1 4 3 1.2\n"
          - Controller 1, Command 4, PID 3, 1.2 
        - Client: "Controller_3 enabled\n"
        - Host: "1 4 3 0.0\n"
          - Controller 1, Command 4, PID 3, 0.0
        - Client: "Controller_3 disabled\n"

  5. SERIAL_CMD_GET_PID_ENABLE
     - Returns the state of the specified PID controller.
     - Accepts only the target ID parameter.
        - Target ID: [1, 4] Int. Values {1, 2, 3, or 4}
          - PID controller to get the enable state from.
        - Param: N/A
     - Example usage:
        - Host: "1 5 1 0.0\n"
          - Controller 1, Command 5, PID 1, 0.0 
        - Client: "Enabled\n" or "Disabled\n"

  6. SERIAL_CMD_PID_SET_P
     - Sets the proportional component of the specified PID controller.
     - Accepts all parameters
        - Target ID: [1, 4] Int. Values {1, 2, 3, or 4}
          - PID controller to set the proportional component of.
        - Param: float, no min/max
          - New value for the proportional component.
     - Example usage:
        - Host: "1 6 2 1.86\n"
          - Controller 1, Command 6, PID 2, 1.86 
        - Client: "Done\n"

  7. SERIAL_CMD_PID_GET_P
     - Returns the proportional component of the specified PID controller.
     - Accepts only the target ID parameter.
        - Target ID: [1, 4] Int. Values {1, 2, 3, or 4}
          - PID controller to get the proportional component from.
        - Param: N/A
     - Example usage:
        - Host: "1 7 2 0.0\n"
          - Controller 1, Command 7, PID 2, 0.0 
        - Client: "1.86\n"

  8. SERIAL_CMD_PID_SET_I
     - Sets the integral component of the specified PID controller.
     - Accepts all parameters
        - Target ID: [1, 4] Int. Values {1, 2, 3, or 4}
          - PID controller to set the integral component of.
        - Param: float, no min/max
          - New value for the integral component.
     - Example usage:
        - Host: "1 8 2 1.86\n"
          - Controller 1, Command 8, PID 2, 0.26 
        - Client: "Done\n"

  9. SERIAL_CMD_PID_GET_I
     - Returns the integral component of the specified PID controller.
     - Accepts only the target ID parameter.
        - Target ID: [1, 4] Int. Values {1, 2, 3, or 4}
          - PID controller to get the integral component from.
        - Param: N/A
     - Example usage:
        - Host: "1 9 2 0.0\n"
          - Controller 1, Command 9, PID 2, 0.0 
        - Client: "0.26\n"

  10. SERIAL_CMD_PID_SET_D
      - Sets the derivative component of the specified PID controller.
      - Accepts all parameters
        - Target ID: [1, 4] Int. Values {1, 2, 3, or 4}
          - PID controller to set the derivative component of.
        - Param: float, no min/max
          - New value for the derivative component.
      - Example usage:
        - Host: "1 10 2 0.03\n"
          - Controller 1, Command 8, PID 2, 0.03 
        - Client: "Done\n"

  11. SERIAL_CMD_PID_GET_D
      - Returns the derivative component of the specified PID controller.
      - Accepts only the target ID parameter.
        - Target ID: [1, 4] Int. Values {1, 2, 3, or 4}
          - PID controller to get the derivative component from.
        - Param: N/A
      - Example usage:
        - Host: "1 11 2 0.0\n"
          - Controller 1, Command 11, PID 2, 0.0 
        - Client: "0.03\n"

  12. SERIAL_CMD_SET_ANGLE_CONV_DEG_MIN
      - Sets the minimum bounds for the ADC reading to degrees conversion for the specified PID controller.
      - Accepts all parameters
        - Target ID: [1, 4] Int. Values {1, 2, 3, or 4}
          - PID controller to set the mimimum bounds of.
        - Param: float, no min/max
          - New value for the minimum bounds.
      - Example usage:
        - Host: "1 12 1 24.68\n"
          - Controller 1, Command 12, PID 1, 24.68
        - Client: "Done\n"

  13. SERIAL_CMD_GET_ANGLE_CONV_DEG_MIN
      - Returns the minimum bounds for the ADC reading to degrees conversion for the specified PID controller.
      - Accepts only the target ID parameter.
        - Target ID: [1, 4] Int. Values {1, 2, 3, or 4}
          - PID controller to get the minimum bounds from.
        - Param: N/A
      - Example usage:
        - Host: "1 13 1 0.0\n"
          - Controller 1, Command 13, PID 1, 0.0 
        - Client: "24.68\n"
          
14. SERIAL_CMD_SET_ANGLE_CONV_DEG_MAX
     - Sets the maximum bounds for the ADC reading to degrees conversion for the specified PID controller.
     - Accepts all parameters
        - Target ID: [1, 4] Int. Values {1, 2, 3, or 4}
          - PID controller to set the maximum bounds of.
        - Param: float, no min/max
          - New value for the maximum bounds.
      - Example usage:
        - Host: "1 12 1 76.48\n"
          - Controller 1, Command 14, PID 1, 76.48
        - Client: "Done\n"

  15. SERIAL_CMD_GET_ANGLE_CONV_DEG_MAX
      - Returns the maximum bounds for the ADC reading to degrees conversion for the specified PID controller.
      - Accepts only the target ID parameter.
        - Target ID: [1, 4] Int. Values {1, 2, 3, or 4}
          - PID controller to get the maximum bounds from.
        - Param: N/A
      - Example usage:
        - Host: "1 15 1 0.0\n"
          - Controller 1, Command 15, PID 1, 0.0 
        - Client: "76.48\n"
          
  16. SERIAL_CMD_SET_ANGLE_JOINT_DEG_MIN    
  17. SERIAL_CMD_GET_ANGLE_JOINT_DEG_MIN   
  18. SERIAL_CMD_SET_ANGLE_JOINT_DEG_MAX
  19. SERIAL_CMD_GET_ANGLE_JOINT_DEG_MAX   
          
  20. SERIAL_CMD_SAVE_SETTINGS
  21. SERIAL_CMD_LOAD_SETTINGS

  22. SERIAL_CMD_SET_MOTOR_SPEED
  23. SERIAL_CMD_GET_MOTOR_SPEED
          
  24. SERIAL_CMD_HOMING_SEQUENCE
  25. SERIAL_CMD_PID_AUTOTUNE