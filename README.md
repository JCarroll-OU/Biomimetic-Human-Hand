# Biomimetic Human Hand
A mostly 3D-printable 21-DOF biologically inspired robotic human hand prototype.
Joints are actuated via 1mm-diameter 304-Stainless-Steel cable driven by motors in the forearm assembly. These cables are fed through 1mm-ID, 2mm-OD PTFE tubing that runs from the forearm to joints. Additionally, these cables will be driven by N20 motors geared down to 300 RPM.

- **DC Motor Controller PCB** 
  - These PCBs implement a PID control algorithm complete with an auto-tuning feature. Each board can support up to 8 motors, so 4 are required to drive the 21 motors present within this design. Each board is designed to operate at 7-12v.
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
