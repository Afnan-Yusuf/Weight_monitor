//A4:CF:12:FF:44:77 MAC address of esp1
//50:02:91:77:C2:2C MAC address of esp2

#include <Arduino.h>
#include "HX711.h"
#include <ESP8266WiFi.h>
#include <espnow.h>

const int LOADCELL_DOUT_PIN = D5; // GPIO 14
const int LOADCELL_SCK_PIN = D6;  // GPIO 12
const int BUTTON_PIN = D7;        // GPIO 13

HX711 scale;
float calibration_factor = 476; 
float w = 0;

uint8_t receiverMac[] = {0xA4, 0xCF, 0x12, 0xFF, 0x44, 0x77}; // Replace with your receiver's MAC address

void onSent(uint8_t *macAddr, uint8_t status) {
}

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.tare(10); 
  Serial.println("Scale initialized");


  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(onSent);
  esp_now_add_peer(receiverMac, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    Serial.println("Tare button pressed");
    scale.tare(10); 
    delay(500); 
  }

  if (scale.is_ready()) {
    float weight = scale.get_units(10); 
    Serial.println(weight);
    w = weight;
    
  } 
   esp_now_send(receiverMac, (uint8_t *)&w, sizeof(w));
}
