#include <VarSpeedServo.h> // To control the speed of our servos
#include <NintendoExtensionCtrl.h> // To use the hacked nunchuck controller

// Initiate some objects
Nunchuk nunchuk;
VarSpeedServo servo1;  
VarSpeedServo servo2;  
VarSpeedServo servo3;  

// Initiate the values
// Distance away from the origin of the second motor in meters
double a0 = 0.017; 
double d0 = 0.086;

// Length of the arms in meters
double d1 = 0.115;
double d2 = 0.115;

// Offsets to make things work due to the way the servo arms attach onto the servos
// there are only fixed positions you can have, meaning we need to tweak them to make it more accurate
// These are in degrees
int offset_shoulder = 13;
int offset_elbow = 3;

// Step size and servo speed
double stp = 0.0009;
int servo_v = 100;

// Initial position in meters
double x = 0.1;
double y = 0;
double z = 0.1;

// Values with the tweaks added
double xval = x + a0;
double yval = y;
double zval = z - d0;

// The rotations the servos need to make in radians
double r1;
double r2;
double r3;


// Calulation functions
double base(double x, double y){
  return atan(y/(x-a0)); 
}

double r(double x, double y, double z){
  return sqrt(pow(x-a0+a0*cos(base(x, y)),2) + pow(y+(a0*sin(base(x, y))),2) + pow(z,2));
}

double elbow(double x, double y, double z){  
  return acos((pow(r(x, y, z),2)-pow(d1,2)-pow(d2,2))/(2*d1*d2));
}

double shoulder(double x, double y, double z){
  return asin(z/r(x, y, z)) + atan((d2*sin(elbow(x, y, z))) / (d1+(d2*cos(elbow(x, y, z)))));
}


// Time to run this baby!
void setup() {
  // Start the serial connection
  Serial.begin(115200);
  Serial.setTimeout(3);

  // Start the nunchuck to run and make sure it's connected
  nunchuk.begin();
  while (!nunchuk.connect()) {
    Serial.println("Nunchuk not detected!");
    delay(1000);
  }

  // Attach my servos with the calibrated values
  servo1.attach(3, 510, 2415); 
  servo2.attach(5, 566, 2365); 
  servo3.attach(6, 678, 2475); 

  // Calculate the angles the servos will need to rotate based on the calibrated values
  // This is for the initial position
  r1 = map(base(xval, yval) * (180/PI), 0, 180, 510, 2500);
  r2 = map(shoulder(xval, yval, zval) * (180/PI), 0, 180, 2500, 570);
  r3 = map(elbow(xval, yval, zval) * (180/PI), 0, 180, 2480, 520);

  // Convert the offsets we had into adjustments in number of PWMs 
  int offset_shoulder_adj = map(offset_shoulder, 0, 180, 570, 2500);
  int offset_elbow_adj = map(offset_elbow, 0, 180, 520, 2480);

  // Send the information to the servos
  servo1.write(r1, 20, false); 
  servo2.write(r2 + offset_shoulder, 20, false); 
  servo3.write(r3 + offset_elbow, 20, false);

  // Print them all out
  Serial.println("r = " + String(r(xval, yval, zval)) +
                 "  base = " + String(base(xval, yval) * (180/PI)) + 
                 "  shoulder = " + String(shoulder(xval, yval, zval) * (180/PI)) + 
                 "  elbow = " + String(elbow(xval, yval, zval) * (180/PI)));
}


void loop() { 
  boolean success = nunchuk.update();  // Get new data from the controller
  
  if(success == true) {  // We have new data!
    nunchuk.update();
    
    int joy_x = nunchuk.joyX();
    int joy_y = nunchuk.joyY();
    int joy_c = nunchuk.buttonC();
    int joy_z = nunchuk.buttonZ();
    int servo_v = 30;

    // According to the controller value, adjust the position of the end effect in the 3D space
    if (joy_x < 128){
      x = x - stp;
    }

    if (joy_x > 128){
      x = x + stp;
    }

    if (joy_y > 128){
      y = y + stp;
    }

    if (joy_y < 128){
      y = y - stp;
    }

    if (joy_c) {
      z = z + stp;
    }

    if (joy_z) {
      z = z - stp;
    }

    xval = x + a0;
    yval = y;
    zval = z - d0;

    // Based on the new 3D position, calculate the angles needed to get there
    r1 = map(base(xval, yval) * (180/PI), 0, 180, 0, 180);
    r2 = map(shoulder(xval, yval, zval) * (180/PI), 0, 180, 180, 0);
    r3 = map(elbow(xval, yval, zval) * (180/PI), 0, 180, 180, 0);
  
    servo1.write(r1, servo_v, false); 
    servo2.write(r2, servo_v, false); 
    servo3.write(r3, servo_v, false);

    Serial.println("x = " + String(x) + 
                   ", y = " + String(y) + 
                   ", z = " + String(z) + 
                   "    " + 
                   "r1 = " + String(r1) + 
                   ", r2 = " + String(r2) + 
                   ", r3 = " + String(r3));
  }
}
