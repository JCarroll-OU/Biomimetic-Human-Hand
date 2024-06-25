// Pin definitions
#define MOTOR_1_ENABLE 3 // D03 [PWM]
#define MOTOR_1A 12 // D12 (Keep D00 [RX] floating so it does not interfere with programming)
#define MOTOR_1B 13 // D13 (Keep D01 [TX] floating so it does not interfere with programming)

#define MOTOR_2_ENABLE 5 // D05 [PWM]
#define MOTOR_2A 2 // D02
#define MOTOR_2B 4 // D04

#define MOTOR_3_ENABLE 6 // D06 [PWM]
#define MOTOR_3A 7 // D07
#define MOTOR_3B 8 // D08

#define MOTOR_4_ENABLE 9 // D09 [PWM]
#define MOTOR_4A 10 // D10 [This is a PWM pin, however it is not used as one]
#define MOTOR_4B 11 // D11 [This is a PWM pin, however it is not used as one]

#define POTENTIOMETER_1 1 // A01 [ADC]
#define POTENTIOMETER_2 2 // A02 [ADC]
#define POTENTIOMETER_3 3 // A03 [ADC]
#define POTENTIOMETER_4 4 // A04 [ADC]

// Set rate of serial communication
#define BAUD_RATE 19200

// PID Default values (for array initialization)
#define PID_DEFUALT_KP 1.00
#define PID_DEFUALT_KI 0.25
#define PID_DEFUALT_KD 0.50
#define PID_DEFAULT_VAL 0.0
#define PID_MAX 5.0
#define JOINT_DEFAULT_MIN_DEG 0.0
#define JOINT_DEFAULT_MAX_DEG 90.0
#define PID_DEFAULT_ENABLE_STATE true

// Error strings, used to reduce the nunber of unique messages in order to save memory
#define ERROR_INVALID_TARGET "Error: Invalid target ID"
#define ERROR_UNKNOWN_COMMAND "Error: Unknown command ID"
#define ERROR_PARAMETER_BOUNDS "Error: Parameter outside acceptable range"
#define ERROR_HOMING_FAILED "Error: Homing sequence failed"
#define COMMAND_COMPLETE "Done" // Sent when no other response is required

// Homing sequence parameters
#define MOTOR_HOMING_SPEED 1
#define MOTOR_HOMING_DELAY 25

// Used to save and load data after power is lost
#include <EEPROM.h>

// Identifier used to start serial commands. A command is only followed if the controller ID matches.
#define CONTROLLER_ID 1 // this is so that numerous controllers can share the same serial port

// Values used to track the speed of the motors, used for serial output
float MOTOR_SPEEDS[] = {PID_DEFAULT_ENABLE_STATE, PID_DEFAULT_ENABLE_STATE, PID_DEFAULT_ENABLE_STATE, PID_DEFAULT_ENABLE_STATE};

// PID Enable state, PID Controllers will not update or use their output to set motor speed unless enable is set to true.
bool PID_ENABLE[] = {PID_DEFAULT_ENABLE_STATE, PID_DEFAULT_ENABLE_STATE, PID_DEFAULT_ENABLE_STATE, PID_DEFAULT_ENABLE_STATE};

// PID targets, inputs, and outputs
float PID_TARGETS[] = {PID_DEFAULT_VAL, PID_DEFAULT_VAL, PID_DEFAULT_VAL, PID_DEFAULT_VAL}; // Set points for pid controllers in degrees
float PID_INPUTS[] = {PID_DEFAULT_VAL, PID_DEFAULT_VAL, PID_DEFAULT_VAL, PID_DEFAULT_VAL};  // Potentiometer readings converted to degrees
float PID_OUTPUTS[] = {PID_DEFAULT_VAL, PID_DEFAULT_VAL, PID_DEFAULT_VAL, PID_DEFAULT_VAL}; // Results of the PID controllers.

// P, I, and D values for all PID controllers
float PID_KP[] = {PID_DEFUALT_KP, PID_DEFUALT_KP, PID_DEFUALT_KP, PID_DEFUALT_KP};
int EEPROM_ADDR_PID_KP[] = {0, 4, 8, 12};
float PID_KI[] = {PID_DEFUALT_KI, PID_DEFUALT_KI, PID_DEFUALT_KI, PID_DEFUALT_KI};
int EEPROM_ADDR_PID_KI[] = {16, 20, 24, 28};
float PID_KD[] = {PID_DEFUALT_KD, PID_DEFUALT_KD, PID_DEFUALT_KD, PID_DEFUALT_KD};
int EEPROM_ADDR_PID_KD[] = {32, 36, 40, 44};

// Internal PID variables 
float PID_LastInput[] = {PID_DEFAULT_VAL, PID_DEFAULT_VAL, PID_DEFAULT_VAL, PID_DEFAULT_VAL};
float PID_Integral[] = {PID_DEFAULT_VAL, PID_DEFAULT_VAL, PID_DEFAULT_VAL, PID_DEFAULT_VAL};
unsigned long PID_LastTime[] = {PID_DEFAULT_VAL, PID_DEFAULT_VAL, PID_DEFAULT_VAL, PID_DEFAULT_VAL};
int RAW_POTENTIOMETERS_RDGS[] = {PID_DEFAULT_VAL, PID_DEFAULT_VAL, PID_DEFAULT_VAL, PID_DEFAULT_VAL};
float CONVERSIONS_ADC_MIN_DEG[] = {PID_DEFAULT_VAL, PID_DEFAULT_VAL, PID_DEFAULT_VAL, PID_DEFAULT_VAL};
int EEPROM_ADDR_ADC_MIN_DEG[] = {48, 52, 56, 60};
float CONVERSIONS_ADC_MAX_DEG[] = {JOINT_DEFAULT_MAX_DEG, JOINT_DEFAULT_MAX_DEG, JOINT_DEFAULT_MAX_DEG, JOINT_DEFAULT_MAX_DEG}; // potentiometers have range of [0, 180] degrees
int EEPROM_ADDR_ADC_MAX_DEG[] = {64, 68, 72, 76};
float JOINT_RANGE_MIN_DEG[] = {JOINT_DEFAULT_MIN_DEG, JOINT_DEFAULT_MIN_DEG, JOINT_DEFAULT_MIN_DEG, JOINT_DEFAULT_MIN_DEG};
int EEPROM_ADDR_JOINT_MIN_DEG[] = {80, 84, 88, 92};
float JOINT_RANGE_MAX_DEG[] = {JOINT_DEFAULT_MAX_DEG, JOINT_DEFAULT_MAX_DEG, JOINT_DEFAULT_MAX_DEG, JOINT_DEFAULT_MAX_DEG}; // potentiometers have range of [0, 180] degrees
int EEPROM_ADDR_JOINT_MAX_DEG[] = {96, 100, 104, 108};

// Updates all values corresponding to the PID controller expect for the PID_INPUTS
void PID_Step(int targetID) {
  // Converts the number within the raw potentiometer readings array to degrees and stores it with pid inputs array
  PID_INPUTS[targetID] = ((float)RAW_POTENTIOMETERS_RDGS[targetID] / 1023.0f) * (CONVERSIONS_ADC_MAX_DEG[targetID] - CONVERSIONS_ADC_MIN_DEG[targetID]);
  float timeChange = (float)(millis() - PID_LastTime[targetID]);
  float error = PID_TARGETS[targetID] - PID_INPUTS[targetID];
  PID_Integral[targetID] += (error * timeChange);
  float derivative = (PID_INPUTS[targetID] - PID_LastInput[targetID]) / timeChange;
  PID_OUTPUTS[targetID] = (PID_KP[targetID] * error) + (PID_KI[targetID] * PID_Integral[targetID]) + (PID_KD[targetID] * derivative);
  PID_OUTPUTS[targetID] = constrain(PID_OUTPUTS[targetID], -PID_MAX, PID_MAX);
  PID_LastInput[targetID] = PID_INPUTS[targetID];
  PID_LastTime[targetID] = millis();
}

// Reads the assigned analog pins corresponding to the potentiometer used with each PID controller.
void Update_Potentiometer_Readings() {
  RAW_POTENTIOMETERS_RDGS[0] = analogRead(POTENTIOMETER_1);
  RAW_POTENTIOMETERS_RDGS[1] = analogRead(POTENTIOMETER_2);
  RAW_POTENTIOMETERS_RDGS[2] = analogRead(POTENTIOMETER_3);
  RAW_POTENTIOMETERS_RDGS[3] = analogRead(POTENTIOMETER_4);
}

/*
  Sets the motor speed of the specified motor.
  @param
    int target accepted values: {1, 2, 3, 4}
        Sets the speed of the motor with an id corresponding to this value.
  @param
    float spd range: [-PID_MAX, PID_MAX]
        Controls both the speed and direction of the motor
*/
void Set_Motor_Speed(int target, float spd) {
  if (abs(spd) > PID_MAX) {
    Serial.println(ERROR_PARAMETER_BOUNDS);
    return;
  }
  int pwmVal = int((abs(spd) / PID_MAX) * 255); // PWM has a range of [0, 255]
  MOTOR_SPEEDS[target - 1] = spd;
  switch (target) {
    case 1: 
      digitalWrite(MOTOR_1A, spd > 0 ? HIGH : LOW); // Set the direction of motor 1
      digitalWrite(MOTOR_1B, spd > 0 ? LOW : HIGH);
      analogWrite(MOTOR_1_ENABLE, pwmVal); // Set the speed for motor 1
      break;
    case 2: 
      digitalWrite(MOTOR_2A, spd > 0 ? HIGH : LOW); // Set the direction motor 2
      digitalWrite(MOTOR_2B, spd > 0 ? LOW : HIGH);
      analogWrite(MOTOR_2_ENABLE, pwmVal); // Set the speed for motor 2
      break;
    case 3: 
      digitalWrite(MOTOR_3A, spd > 0 ? HIGH : LOW); // Set the direction motor 3
      digitalWrite(MOTOR_3B, spd > 0 ? LOW : HIGH);
      analogWrite(MOTOR_3_ENABLE, pwmVal); // Set the speed for motor 3
      break;
    case 4: 
      digitalWrite(MOTOR_4A, spd > 0 ? HIGH : LOW); // Set the direction motor 4
      digitalWrite(MOTOR_4B, spd > 0 ? LOW : HIGH);
      analogWrite(MOTOR_4_ENABLE, pwmVal); // Set the speed for motor 4
      break;
    default:
      Serial.println(ERROR_INVALID_TARGET);
      break;
  }
}

/*
  Reads potentiometers, updates PIDs, and sets motor speed
  @param none
*/
void Update_PID_Controllers() {
  Update_Potentiometer_Readings();
  for (int i = 0; i < 4; i++) {
    if (PID_ENABLE[i]) {
      PID_Step(i);
      Set_Motor_Speed(i + 1, PID_OUTPUTS[i]);
    }
  }
}

/*
  Sets the data direction registers for the necessary pins
  @param none
*/
void Setup_IO() {
  pinMode(MOTOR_1_ENABLE, OUTPUT);
  pinMode(MOTOR_1A, OUTPUT);
  pinMode(MOTOR_1B, OUTPUT);
  pinMode(POTENTIOMETER_1, INPUT);

  pinMode(MOTOR_2_ENABLE, OUTPUT);
  pinMode(MOTOR_2A, OUTPUT);
  pinMode(MOTOR_2B, OUTPUT);
  pinMode(POTENTIOMETER_2, INPUT);

  pinMode(MOTOR_3_ENABLE, OUTPUT);
  pinMode(MOTOR_3A, OUTPUT);
  pinMode(MOTOR_3B, OUTPUT);
  pinMode(POTENTIOMETER_3, INPUT);

  pinMode(MOTOR_4_ENABLE, OUTPUT);
  pinMode(MOTOR_4A, OUTPUT);
  pinMode(MOTOR_4B, OUTPUT);
  pinMode(POTENTIOMETER_4, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);
}

/*
  Writes 4 bytes to the EEPROM starting at the specified location.
  @param
    int location: [0, 1023]
      Location in EEPROM memory (in bytes) to start writing at.
  @param
    float val:
      Value to write. Starting at the specifed location. A float is 4 bytes.

*/
void EEPROM_write_float(int location, float val) {
  byte* b = (byte*)&val;
  EEPROM.update(location + 0, b[0]);
  EEPROM.update(location + 1, b[1]);
  EEPROM.update(location + 2, b[2]);
  EEPROM.update(location + 3, b[3]);
}

/*
  Reads 4 bytes from the EEPROM starting at the specified location.
  @param
    int location: [0, 1023]
      Location in EEPROM memory (in bytes) to start reading at. A float is 4 bytes.
  @return
    float val:
      Value read from EEPROM.

*/
float EEPROM_read_float(int location) {
  byte b[] = { EEPROM.read(location + 0),
              EEPROM.read(location + 1),
              EEPROM.read(location + 2),
              EEPROM.read(location + 3) };
  float result = *((float*)b);
  return isnan(result) ? 0.0f : result;
}

/*
  Calculates the ADC_MIN_DEG and ADC_MAX_DEG values based on potentiometer
  response to driving the motors in either direction for some period of time.
  If the motor is active but no change in the potentiometer reading is
  detected, the current ADC reading is used to calculate the required bounds
  used in the conversion such that they correspond with the specified min. and 
  max joint angles (a measure in degrees).
  @param
    int target: accepted values = {1, 2, 3, 4}
        Perform the homing sequence on this motor controller.

*/
void Homing_Sequence(int target) {
  // move the motors forward until position change is no longer registered
  Update_Potentiometer_Readings();
  int upper_adc_bounds = RAW_POTENTIOMETERS_RDGS[target - 1]; // adc reading corresponding to max flexure (~90 degrees)
  Set_Motor_Speed(target, MOTOR_HOMING_SPEED);
  delay(MOTOR_HOMING_DELAY);
  Update_Potentiometer_Readings();
  int i = 0;
  while (RAW_POTENTIOMETERS_RDGS[target - 1] != upper_adc_bounds) {
    upper_adc_bounds = RAW_POTENTIOMETERS_RDGS[target - 1];
    delay(MOTOR_HOMING_DELAY);
    i++; // i is the delay index tracker
    Update_Potentiometer_Readings();
  } // continously check that joint is moving
  Set_Motor_Speed(target, 0);

  // move the motors backwards until position change is no longer registered
  int lower_adc_bounds = RAW_POTENTIOMETERS_RDGS[target - 1]; // adc reading corresponding to min flexure (~0 degrees)
  Set_Motor_Speed(target, -MOTOR_HOMING_SPEED);
  delay(MOTOR_HOMING_DELAY);
  Update_Potentiometer_Readings();
  while (RAW_POTENTIOMETERS_RDGS[target - 1] != lower_adc_bounds) {
    lower_adc_bounds = RAW_POTENTIOMETERS_RDGS[target - 1];
    delay(MOTOR_HOMING_DELAY);
    Update_Potentiometer_Readings();
  } // continously check that joint is moving
  Set_Motor_Speed(target, 0);

  // check that the following steps will result in a defined value, if not return homing failed
  if ((lower_adc_bounds - upper_adc_bounds) == 0 || (JOINT_RANGE_MIN_DEG[target - 1] - JOINT_RANGE_MAX_DEG[target - 1]) == 0) {
    Serial.println(ERROR_HOMING_FAILED);
    return;
  } else { // if either of the values above are zero, then the following calculation cannot be made
    // calculate the required upper and lower bounds to output JOINT_MIN_DEG to JOINT_MAX_DEG degrees given adc readings
    CONVERSIONS_ADC_MIN_DEG[target - 1] = ((lower_adc_bounds * JOINT_RANGE_MAX_DEG[target - 1]) - (JOINT_RANGE_MIN_DEG[target - 1] * upper_adc_bounds)) / (lower_adc_bounds - upper_adc_bounds);
    CONVERSIONS_ADC_MAX_DEG[target - 1] = ((lower_adc_bounds * JOINT_RANGE_MAX_DEG[target - 1]) - (JOINT_RANGE_MIN_DEG[target - 1] * (upper_adc_bounds - 1023)) - (JOINT_RANGE_MAX_DEG[target - 1] * 1023)) / (lower_adc_bounds - upper_adc_bounds);
    Serial.println(COMMAND_COMPLETE);
  }
}

/*
  Processes a command by its ID, target ID, and parameter (if applicable).
  @param
    int cmd: [0, 22]
      Command identifier. See DC Motor Controller Serial Command Assembler program for list of commands.
  @param
    int target: [1, 4]
      Target identifier. Motor or controller targetted by command. 0 if unused.
  @param
    float param: 
      Parameter for command. 0.0f if unused.

*/
void Process_Command(int cmd, int target, float param) {
  if (cmd == 0) { // SERIAL_CMD_EMPTY
    Serial.println(((float)millis() / 1000.0f)); // respond to handshake request with current runtime in seconds
  } else if (cmd == 1) { // SERIAL_CMD_SET_TARGET_ANGLE
    if (param > JOINT_RANGE_MAX_DEG[target - 1] || param < JOINT_RANGE_MIN_DEG[target - 1]) {
      Serial.println(ERROR_PARAMETER_BOUNDS);
      return;
    }
    PID_TARGETS[target - 1] = param;
    Serial.println(COMMAND_COMPLETE);
  } else if (cmd == 2) { // SERIAL_CMD_GET_TARGET_ANGLE
    Serial.println(String(PID_TARGETS[target - 1]));
  } else if (cmd == 3) { // SERIAL_CMD_GET_CURRENT_ANGLE
    Serial.println(String(PID_INPUTS[target - 1]));
  } else if (cmd == 4) { // SERIAL_CMD_SET_PID_ENABLE
    PID_ENABLE[target - 1] = param != 0;
    String header = "Controller_" + String(target) + " disabled";
    if (PID_ENABLE[target - 1])
      header = "Controller_" + String(target) + " enabled";
    Serial.println(header);
  } else if (cmd == 5) { // SERIAL_CMD_GET_PID_ENABLE
    Serial.println(PID_ENABLE[target - 1] ? "Enabled" : "Disabled");
  } else if (cmd == 6) { // SERIAL_CMD_PID_SET_P
    PID_KP[target - 1] = param;
    Serial.println(COMMAND_COMPLETE);
  } else if (cmd == 7) { // SERIAL_CMD_PID_GET_P
    Serial.println(PID_KP[target - 1]);
  } else if (cmd == 8) { // SERIAL_CMD_PID_SET_I
    PID_KI[target - 1] = param;
    Serial.println(COMMAND_COMPLETE);
  } else if (cmd == 9) { // SERIAL_CMD_PID_GET_I
    Serial.println(PID_KI[target - 1]);
  } else if (cmd == 10) { // SERIAL_CMD_PID_SET_D
    PID_KD[target - 1] = param;
    Serial.println(COMMAND_COMPLETE);
  } else if (cmd == 11) { // SERIAL_CMD_PID_GET_D
    Serial.println(PID_KD[target - 1]);
  } else if (cmd == 12) { // SERIAL_CMD_SET_ANGLE_CONV_DEG_MIN
    CONVERSIONS_ADC_MIN_DEG[target - 1] = param;
    Serial.println(COMMAND_COMPLETE);
  } else if (cmd == 13) { // SERIAL_CMD_GET_ANGLE_CONV_DEG_MIN
    Serial.println(CONVERSIONS_ADC_MIN_DEG[target - 1]);
  } else if (cmd == 14) { // SERIAL_CMD_SET_ANGLE_CONV_DEG_MAX
    CONVERSIONS_ADC_MAX_DEG[target - 1] = param;
    Serial.println(COMMAND_COMPLETE);
  } else if (cmd == 15) { // SERIAL_CMD_GET_ANGLE_CONV_DEG_MAX
    Serial.println(CONVERSIONS_ADC_MAX_DEG[target - 1]);
  } else if (cmd == 16) { // SERIAL_CMD_SET_ANGLE_JOINT_DEG_MIN
    JOINT_RANGE_MIN_DEG[target - 1] = param;
    Serial.println(COMMAND_COMPLETE);
  } else if (cmd == 17) { // SERIAL_CMD_GET_ANGLE_JOINT_DEG_MIN
    Serial.println(JOINT_RANGE_MIN_DEG[target - 1]);
  } else if (cmd == 18) { // SERIAL_CMD_SET_ANGLE_JOINT_DEG_MAX
    JOINT_RANGE_MAX_DEG[target - 1] = param;
    Serial.println(COMMAND_COMPLETE);
  } else if (cmd == 19) { // SERIAL_CMD_GET_ANGLE_JOINT_DEG_MAX
    Serial.println(JOINT_RANGE_MAX_DEG[target - 1]);
  } else if (cmd == 20) { // SERIAL_CMD_SAVE_SETTINGS
    for (int i = 0; i < 4; i++) { 
      EEPROM_write_float(EEPROM_ADDR_PID_KP[i], PID_KP[i]);
      EEPROM_write_float(EEPROM_ADDR_PID_KI[i], PID_KI[i]);
      EEPROM_write_float(EEPROM_ADDR_PID_KD[i], PID_KD[i]);
      EEPROM_write_float(EEPROM_ADDR_ADC_MIN_DEG[i], CONVERSIONS_ADC_MIN_DEG[i]);
      EEPROM_write_float(EEPROM_ADDR_ADC_MAX_DEG[i], CONVERSIONS_ADC_MAX_DEG[i]);
      EEPROM_write_float(EEPROM_ADDR_JOINT_MIN_DEG[i], JOINT_RANGE_MIN_DEG[i]);
      EEPROM_write_float(EEPROM_ADDR_JOINT_MAX_DEG[i], JOINT_RANGE_MAX_DEG[i]);
    }
    Serial.println(COMMAND_COMPLETE);
  } else if (cmd == 21) { // SERIAL_CMD_LOAD_SETTINGS
    for (int i = 0; i < 4; i++) { 
      PID_KP[i] = EEPROM_read_float(EEPROM_ADDR_PID_KP[i]);
      PID_KI[i] = EEPROM_read_float(EEPROM_ADDR_PID_KI[i]);
      PID_KD[i] = EEPROM_read_float(EEPROM_ADDR_PID_KD[i]);
      CONVERSIONS_ADC_MIN_DEG[i] = EEPROM_read_float(EEPROM_ADDR_ADC_MIN_DEG[i]);
      CONVERSIONS_ADC_MAX_DEG[i] = EEPROM_read_float(EEPROM_ADDR_ADC_MAX_DEG[i]);
      JOINT_RANGE_MIN_DEG[i] = EEPROM_read_float(EEPROM_ADDR_JOINT_MIN_DEG[i]);
      JOINT_RANGE_MAX_DEG[i] = EEPROM_read_float(EEPROM_ADDR_JOINT_MAX_DEG[i]);
    }
    Serial.println(COMMAND_COMPLETE);
  } else if (cmd == 22) { // SERIAL_CMD_SET_MOTOR_SPEED
    Set_Motor_Speed(target, param);
    Serial.println(COMMAND_COMPLETE);
  } else if (cmd == 23) { // SERIAL_CMD_GET_MOTOR_SPEED
    Serial.println(MOTOR_SPEEDS[target - 1]);
  } else if (cmd == 24) { // SERIAL_CMD_HOMING_SEQUENCE
    Homing_Sequence(target); // this will handle to response to this command, no need for Serial.println(COMMAND_COMPLETE);
  } else { // UNKNOWN COMMAND
    Serial.println(ERROR_UNKNOWN_COMMAND);
  }
}

/*
  Check if serial port is being written to, if it is process the tranmission. Checks if this command is 
  meant for this controller and then sends the semi-processed (converted from string to int or float) 
  command to the process command function using the command ID, target ID, and parameter. This should be
  called during 'loop.' It will automatically call 'Process_Command'on complete transmission if the 
  controller ID matches.
*/
void Process_Serial() {
  while (Serial.available() > 0) {
    int ctrlID = Serial.readStringUntil(' ').toInt();
    int cmdID = Serial.readStringUntil(' ').toInt();
    int trgID = Serial.readStringUntil(' ').toInt();
    float cmdParam = Serial.readStringUntil('\n').toFloat();
    if (ctrlID == CONTROLLER_ID)
      Process_Command(cmdID, trgID, cmdParam);
  }
}

// Called once during startup. Enables serial and sets up IO.
void setup() {
  Serial.begin(BAUD_RATE);
  Setup_IO();
}

// Called once per 'frame'. The debug LED will turn on and off over a 50+ ms period.
// If you can count the number of flickers per second, it is running too slow!
// This should be running at least 10 times per second!
void loop() {
  Process_Serial();

  digitalWrite(LED_BUILTIN, HIGH);
  delay(25);

  // Reads the potentiometers and converts to degrees, then updates the PID controllers, and finally, sets the motor speeds.
  Update_PID_Controllers();

  digitalWrite(LED_BUILTIN, LOW);
  delay(25);
}