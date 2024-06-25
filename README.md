# Biomimetric Human Hand
A mostly 3D-printable 21-DOF biologically inspired robotic human hand prototype.

## Progess Report:
**March 2024:** Started preliminary research and development. 
- Explored multiple forms of actuation including hydraulic and electric.
- Opted for electric due to size, simplicity, cost, and reliability.
- Formulated general design constraints for the robot.

**April 2024:** Development of DC Motor Controller PCB.
- Designed, tested, and revised boards, eventually arriving at the third major milestone, Mk 3. 
- Ordered prototypes via PCBWay.
- Wrote the AVR code necessary to implement motor control, SPI, and ADC.

**May 2024:** Controls R&D
- Received and assembled prototype board.
- Unable to read device signature.
- Continuity check: OK
- Signal integrity: Unable to access oscilliscope, ENGR lab closed.
- Hiatus, I feel dumb.

**June 2024:** Continued controls R&D
- Opted to keep things simple by using Arduino based controllers and serial communication.
- Ordered Mk. 4 DC Motor Controller PCB prototypes with 14-day lead-time. 
- Finalized PID controller code for Arduino Nanos. 

**June 25<sup>th</sup>, 2024:** Created GitHub repository and made initial commit.
- Setup file structure such that concurrent and deprecated parts of the project are in separate folders.
- Separated project components into software and hardware categories.
- Changed the shape of the 'metacarpus' to allow for the thumb to flex towards the palm of the hand. 
  - Parts are currently very difficult to successfully print and prepare for use. Revise parts such that they can be printed with ease.
  - The changes to the 'skeletal' system of the robot means that the kinemtics must be recalculated. 
  - Without the control cable and PTFE tubing on-hand, theres no way to test the range of motion without manually manipulating the joints. 

## Project Highlights:
- **DC Motor Controller PCB** 
  - This serves as the interface between hardware and software for this project. Each board contains 2 Arduino Nano microcontrollers, which each implement 4 PID controllers, for a total of 8 PID controllers per board. There are 25 motors and joints within the current design which mimic the natural range of motion of the human hand as closely as possible.
  ![Mk. 1](/Renders/DC_Motor_Controller_2024-May-16_01-15-25PM-000_CustomizedView20484802570.png)
  - Used more microcontrollers than necessary, driving the project over-budget. 
  ![Mk. 2](/Renders/DC_Motor_Controller_2024-May-17_01-13-07PM-000_CustomizedView9308964263.png)
  - Microcontroller too small to reliably solder by hand. Too many voltage regulators, what was I thinking?
  ![Mk. 3](/Renders/DC_Motor_Controller_Mk3_2024-May-31_03-53-12AM-000_CustomizedView27002214263_png.png)
  - See 'Reasons for deprecation' file in project folder. TL:DR; Unable to program and unable to identify cause without proper equipment. _K.I.S,S!_
  ![Mk. 4](/Renders/DC_Motor_Controller_Mk4_2024-Jun-25_07-05-43PM-000_CustomizedView16519912145_png.png)
  - Current version of the DC Motor Controller PCB. Controls 8 motors with a PID Controller, is programmable in-circuit, and has the lowest production cost of all models. 
  ![Mk. 4 Schematic](/Designs/Concurrent/DC%20Motor%20Controller/Mk4/Schematic.png)
  - Schematic of Mk. 4 DC Motor Controller PCB. 
  ![Mk. 4 Board Layout](/Designs/Concurrent/DC%20Motor%20Controller/Mk4/Board%20Layout.png)
  - PCB Layout and dimensions of Mk. 4 DC Motor Controller PCB. 

- **'Skeletal' System** 
  - Many specialized parts are used in the design of a robotic hand. To keep costs low, most of these parts are 3D-printed expect where structural stability is a concern, in which case readily available metal parts are used. This is meant to closely mimic the range of motion of the human hand, expect where deemed impractical due to cost or complexity. All parts are designed for FDM printing, however, better results may be acheived by using another manufacturing method.
  ![Phalanx Assembly: 3D-Printed Parts only](/Renders/Phalanx_Assembly_2024-Jun-23_05-39-12PM-000_CustomizedView3688566158_png.png)
  - Palm assembly in black (10 parts) and fingers in white (3 parts each). 3D-printed parts only.
  ![Phalanx Assembly: Complete](/Renders/Phalanx_Assembly_2024-Jun-24_08-13-17PM-000_CustomizedView18257921723_png.png)
  - Complete hand assembly with updated metacarpus and all hardware expect control cables.
  ![Concept Art: Production at scale](/Renders/Sheet%20Metal%20Phalanx%20-%20Concept%20Art%20for%20Mk2.png)
  - Concept art for a future version of this project. This is meant to be produced at scale where the cost would be approximately the same as the 3D-printed counterparts.