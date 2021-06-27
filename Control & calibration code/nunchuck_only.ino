#include <NintendoExtensionCtrl.h> // Library for the nunchuck

// Initialise the nunchuck object
Nunchuk nunchuk;


void setup() {
  // Start serial communication between nunchuck and laptop
  Serial.begin(115200);

  // Begin connection, if non connected, alert us
  nunchuk.begin();
  while (!nunchuk.connect()) {
    Serial.println("Nunchuk not detected!");
    delay(1000);
  }
}

void loop() {
  boolean success = nunchuk.update();  // Get new data from the controller

  if(success == true) {  // We have new data!
    nunchuk.update();
    
    int x_val = nunchuk.joyX();
    int y_val = nunchuk.joyY();
    int C_button = nunchuk.buttonC();
    int Z_button = nunchuk.buttonZ();

    // Print values from the nunchuck
    Serial.print("x: " + String(x_val) + " y: " + String(y_val) + " C button: " + String(C_button) + " Z button: " + String(Z_button) + "\n");
  }
}
