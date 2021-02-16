#include <VarSpeedServo.h> 
#include <NintendoExtensionCtrl.h>

Nunchuk nunchuk;

VarSpeedServo servo1;  
VarSpeedServo servo2;  
VarSpeedServo servo3;  

double a0 = 0.017;
double d0 = 0.085;

double d1 = 0.115;
double d2 = 0.115;

double stp = 0.001;
int servo_v = 25;

double x = 0.1;
double y = 0;
double z = 0.1;

double xval = x + a0;
double yval = y;
double zval = z - d0;

double r1;
double r2;
double r3;

// Declare some functions
double base(double x, double y){
  return atan(y/(x-a0)); 
}

double r(double x, double y, double z){
  return sqrt(pow(x-a0+a0*cos(base(x, y)),2) + pow(y+a0*sin(base(x, y)),2) + pow(z,2));
}

double elbow(double x, double y, double z){  
  return acos((pow(r(x, y, z),2)-pow(d1,2)-pow(d2,2))/(2*d1*d2));
}

double shoulder(double x, double y, double z){
  return asin(z/r(x, y, z)) + atan((d2*sin(elbow(x, y, z)))/(d1+d2*cos(elbow(x, y, z))));
}


// Time to run this baby!
void setup() {
  Serial.begin(115200);
  Serial.setTimeout(3);
  
  nunchuk.begin();

  while (!nunchuk.connect()) {
    Serial.println("Nunchuk not detected!");
    delay(1000);
  }
  
  servo1.attach(3); 
  servo2.attach(5); 
  servo3.attach(6);  

  r1 = map(base(xval, yval) * (180/PI), 0, 180, 0, 180);
  r2 = map(shoulder(xval, yval, zval) * (180/PI), 0, 180, 180, 0);
  r3 = map(elbow(xval, yval, zval) * (180/PI), 0, 180, 180, 0);
  
  servo1.write(r1, 20, false); 
  servo2.write(r2, 20, false); 
  servo3.write(r3, 20, false);

  Serial.println("base = " + String(r1) + 
                 "shoulder = " + String(r2) + 
                 "elbow = " + String(r3));
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
    
    if (joy_x < 127){
      x = x - stp;
    }

    if (joy_x > 127){
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

    // Make sure to account for the nature of the servos
    r1 = map(base(xval, yval) * (180/PI), 0, 180, 0, 180);
    r2 = map(shoulder(xval, yval, zval) * (180/PI), 0, 180, 180, 0);
    r3 = map(elbow(xval, yval, zval) * (180/PI), 0, 180, 180, 0);
  
    servo1.write(r1, servo_v, false); 
    servo2.write(r2, servo_v, false); 
    servo3.write(r3, servo_v, false);

    Serial.println("x = " + String(x) + 
                   ", y = " + String(y) + 
                   ", z = " + String(z));
  delay(2);
  }
}
