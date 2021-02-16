# MUEEC_robot_arm
Geometrically calculated inverse kinematics code for both MATLAB and Arduino with the simulation done in MATLAB for a 3DOF serial arm

## Geometrically calculated Inverse Kinematics
Given the position of the end effector calculate the angles of each individual servo such that the end effector is exactly at the target position
The functions are calculated by projecting the 3D robot arm onto a 2D plane to simplify the problem.

This is the paper I based it off of, note I said BASED because some of the equations are WRONG...yeah...
https://www.researchgate.net/publication/328583527_A_Geometric_Approach_to_Inverse_Kinematics_of_a_3_DOF_Robotic_Arm

* base = angle of base servo
* shoulder = angle of second servo
* elbow = angle of the 3 servo

## MATLAB code:
The 3 links are simulated and plotted in 3D to make sure the solution is exact.  

## Arduino code:
Necessary libraries 
* nunchuck library: NintendoExtensionCtrl
* servo speed library: VarSpeedServo

A wii nunchuck is used to dictate the position in 3D to be converted into angles for the servo


