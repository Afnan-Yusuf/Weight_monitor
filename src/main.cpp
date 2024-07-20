#include <Arduino.h>
#include "HX711.h"

const int LOADCELL_DOUT_PIN = D5; // GPIO 14
const int LOADCELL_SCK_PIN = D6;  // GPIO 12
const int BUTTON_PIN = D7;        // GPIO 13

HX711 scale;
float calibration_factor = 476; 

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.tare(10); 
  Serial.println("Scale initialized");
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("Tare button pressed");
    scale.tare(); 
    delay(500); 
  }

  if (scale.is_ready()) {
    float weight = scale.get_units(10); 
    Serial.print("Weight: ");
    Serial.print(weight, 2);
    Serial.println(" kg");
  } 
}
