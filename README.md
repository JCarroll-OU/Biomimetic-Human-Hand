# Biomimetic Human Hand
A mostly 3D-printable 21-DOF biologically inspired robotic human hand prototype.
Joints are actuated via 1mm-diameter 304-Stainless-Steel cable driven by motors in the forearm assembly. These cables are fed through 1mm-ID, 2mm-OD PTFE tubing that runs from the forearm to joints. Additionally, these cables will be driven by N20 motors geared down to 300 RPM.

## Progess Report:
**March 2024:** Started preliminary research and development. 
- Formulated general design constraints for the robot.
- Explored multiple forms of actuation including hydraulic and electric.
- Opted for electric due to size, simplicity, cost, and reliability.

**April 2024:** Development of DC Motor Controller PCB.
- Designed, tested, and revised boards, eventually arriving at the third major milestone, Mk 3. 
- Ordered prototypes via PCBWay.
- Wrote the AVR code necessary to implement motor control, SPI, and ADC.

**May 2024:** Controls R&D
- Received and assembled prototype boards.
- Unable to read device signature.
- Continuity check: OK
- Signal integrity: Unable to access oscilliscope, engineering lab is temporarly closed.
- Hiatus, I feel dumb.

**June 2024:** Continued controls R&D
- Opted to keep things simple by using Arduino based controllers and serial communication.
- Ordered Mk. 4 DC Motor Controller PCB prototypes with 14-day lead-time. 
- Finalized PID controller code for Arduino Nanos. 

**June 25<sup>th</sup>, 2024:** Created GitHub repository and made initial commit.
- Setup file structure such that concurrent and deprecated parts of the project are in separate folders.
- Separated project components into software and hardware categories.
- Changed the shape of the 'metacarpus' to allow for the thumb to flex towards the palm of the hand. 

**Recent changes:** Started designed forearm assembly, which houses the motors and controller PCBs. 
- Integrated MS90S servo into wrist assembly. 
- Fixed clearance issues that resulted in low success rate for FDM prints.
- More renders and documentation. 

## Project Highlights:
- **DC Motor Controller PCB** 
  - These PCBs implement a PID control algorithm complete with an auto-tuning feature. Each board can support up to 8 motors, so 4 are required to drive the 25 joints present within this design. Each board is designed to operate at 7-12v.
  ![Mk. 4 Schematic](/Designs/Concurrent/DC%20Motor%20Controller/Mk4/Schematic.png)
  - Schematic of Mk. 4 DC Motor Controller PCB. 
  ![Mk. 4 Board Layout](/Designs/Concurrent/DC%20Motor%20Controller/Mk4/Board%20Layout.png)
  - PCB Layout and dimensions of Mk. 4 DC Motor Controller PCB. 

- **'Skeletal' System** 
  - Cost was a major design consideration for this prototype. Most parts are designed for 3D-printing (FDM but SLS/SLA is preferrable). Those that are not, are readily available and thus, cheap. 
  ![WIP: Forearm Assembly, Top](/Renders/assembly%20guide%20top.png)
  ![WIP: Forearm Assembly, Right](/Renders/assembly_guide_right.png)
  ![WIP: Forearm Assembly, Render](/Renders/Phalanx_Assembly_2024-Jun-28_02-02-48AM-000_CustomizedView21154948335_png.png)
  - Finger assemblies in black, palm assembly in yellow, and wrist in blue.
  ![Concept Art: Production at scale](/Renders/Sheet%20Metal%20Phalanx%20-%20Concept%20Art%20for%20Mk2.png)
  - Folded sheet metal finger assembly concept art.

  ### This is a work in progress!
  More detailed reports, test results, and notes are available upon request. Contact me or see the license for information regarding the use, reproduction, and distribution of any of the content associated with this project. Thank you!
