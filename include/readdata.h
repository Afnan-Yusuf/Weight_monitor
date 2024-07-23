#pragma once
#include "variables.h"

const int LOADCELL_DOUT_PIN = D5; // GPIO 14
const int LOADCELL_SCK_PIN = D6;  // GPIO 12

HX711 scale;

float calibration_factor = 476;


float weight = 0;

#define zbutton D7 // GPIO 13
#define fbutton D8

float  weightmin = 50;
float weightmax = 1100;

void initloadcell()
{
    scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    scale.tare(10);
    pinMode(zbutton, INPUT_PULLUP);
}
void readvalue()
{
    if (digitalRead(zbutton) == LOW)
    {
        Serial.println("Tare button pressed");
        scale.tare(10);
        delay(500);
    }
    if (digitalRead(fbutton) == LOW)
    {
        weightmax = weight;
            delay(500);
    }
    if (scale.is_ready())
    {
        weight = scale.get_units(10);
        Serial.println(weight);
    }
    mapped_weight = map(weight, 0, 1500, weightmin, weightmax);
}