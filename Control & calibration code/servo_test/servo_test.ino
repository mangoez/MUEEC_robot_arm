#include <VarSpeedServo.h> // Variable speed control for servo

// Initiate servo objects
VarSpeedServo servo1;  
VarSpeedServo servo2;  
VarSpeedServo servo3;  

// Attach them, this is just a simple test so we are no calibrating them
// just making sure they are connected
void setup() {
  servo1.attach(3); 
  servo2.attach(5); 
  servo3.attach(6); 
} 

// What this will do is loop between two different positions for each servo at a specified speed
void loop() {
  servo1.write(90, 20, false);  
  servo2.write(90, 20, false); 
  servo3.write(90, 20, false);  
  delay(2500);
  servo1.write(0, 20, false); 
  servo2.write(0, 20, false);
  servo3.write(0, 20, false);
  delay(2500);  
}
