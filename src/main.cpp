//A4:CF:12:FF:44:77 MAC address of esp1
//50:02:91:77:C2:2C MAC address of esp2

#include <Arduino.h>
#include "readdata.h"
#include "variables.h"
#include "sentdata.h"


void setup() {
  initespnow();
  initloadcell();
  Serial.begin(115200);
}

void loop() {

  readvalue();
  sentdata();
   
}
