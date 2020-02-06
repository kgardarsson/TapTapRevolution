#include "Piezo.h"

Piezo piezos[8];
int preChannel;
int newChannel;
int lightValue;

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 2500) /* wait for serial monitor */ ;
  piezos[0].populate(A13, 30, 36);
  piezos[1].populate(A12, 29, 38);
  piezos[2].populate(A16, 37, 40);
  piezos[3].populate(A15, 38, 41);
}


void loop() {
  //Serial.println(map(analogRead(A20), 0, 1024, 1, 8));
  
  for (int i=0; i<4; i++) {
    piezos[i].readInput();
    /*
    Serial.print("Piezo[");
    Serial.print(i);
    Serial.print("] = ");
    Serial.print(piezos[i].returnValue());
    Serial.print(", channel: ");
    Serial.print(piezos[i].channel);
    Serial.print("    ");
    */
  }
  Serial.println(analogRead(A14));

  
  newChannel = map(analogRead(A20), 0, 1023, 1, 4);
  if (newChannel != preChannel) {
    for (int i=0; i<4; i++) {
      piezos[i].channel = newChannel;
    }
  }  

/*
  //for light sensor
  lightValue = map(analogRead(A14), 0, 1023, 0, 24);
  usbMIDI.sendPitchBend(lightValue, newChannel);
  */

  preChannel = newChannel;
  
  delay(20);
}
