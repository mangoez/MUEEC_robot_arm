#include <VarSpeedServo.h> 

VarSpeedServo servo1;  
VarSpeedServo servo2;  
VarSpeedServo servo3;  


void setup() {
  // First we attach our servo + indicate the range of PWM it operates in
  // The order of input is pin_number, minimum PWM, maximum PWM
  // This will specify your 180 degree range
  // These are the ones I use for mine as an indicator of the rough values you'll be using
  servo1.attach(3, 510, 2415); 
  servo2.attach(5, 566, 2365); 
  servo3.attach(6, 678, 2475);

  servo1.write(0, 20, false);  // This would be 0 degrees
  servo2.write(90, 20, false); // This would be 90 degrees
  servo3.write(90, 20, false); // This would be 90 degrees
}

void loop() {
  // put your main code here, to run repeatedly:

}
