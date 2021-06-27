# MUEEC_robot_arm
Welcome!
If you are here you either have landed on my nerd turf and/or you are looking for the code to control a robot arm. 
In summary, this is operated by geometrically calculated inverse kinematics code for both MATLAB and Arduino with the simulation done in MATLAB for a 3DOF serial arm. This is all controlled by a single arduino and runs in real time with decent precision of the end effector. 

In the folder there is also code to calibrate and test the Wii nunchuck as well as the servos for your individual projects.

## Geometrically calculated Inverse Kinematics
Given the position of the end effector calculate the angles of each individual servo such that the end effector is exactly at the target position
The functions are calculated by projecting the 3D robot arm onto a 2D plane to simplify the problem.

This is the paper I based it off of, note I said BASED because some of the equations are WRONG...yeah...
https://www.researchgate.net/publication/328583527_A_Geometric_Approach_to_Inverse_Kinematics_of_a_3_DOF_Robotic_Arm

* base = angle of base servo
* shoulder = angle of second servo
* elbow = angle of the 3 servo

## MATLAB simulation code:
The 3 links are simulated and plotted in 3D to make sure the geometric solution is exact.  

## Arduino code:
Necessary libraries 
* nunchuck library: NintendoExtensionCtrl
* servo speed library: VarSpeedServo
A wii nunchuck is used to dictate the position in 3D to be converted into angles for the servo

**robot_control_geometric** 
Is the actual program used to calculate the servo angles in order to position the end effector in 3D space. 

**nunchuck_only**
Connect and print the values from the nunchuck to test the connection and values of the joystick _ buttons

**set_servo_range** 
This is designed to be used with the calibrating tool we provided that gives you 5 degree resolution of where your servo is.

Use that and this program to set the minimum and maximum values of your servo which correspond to 0 - 180 degrees for each individual servo. 

**Servo test**
Just checks the connection and literally run the servo between two positions, introduces the package for variable speed control of the servo. 


