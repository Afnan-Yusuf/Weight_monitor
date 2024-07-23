#include "variables.h"
uint8_t receiverMac[] = {0xA4, 0xCF, 0x12, 0xFF, 0x44, 0x77}; // Replace with your receiver's MAC address

void onSent(uint8_t *macAddr, uint8_t status) {
}
void initespnow(){
    WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(onSent);
  esp_now_add_peer(receiverMac, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);
}

void sentdata(){
    esp_now_send(receiverMac, (uint8_t *)&mapped_weight, sizeof(mapped_weight));
}