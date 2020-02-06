#include "Piezo.h"

Piezo piezos[8];
LightSensor ldrLeft;
LightSensor ldrRight;
int oldChannel;
int channel;
int lightValue;

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 2500) /* wait for serial monitor */ ;
  piezos[0].populate(A13, 30, 36);
  piezos[1].populate(A12, 29, 38);
  piezos[2].populate(A16, 37, 40);
  piezos[3].populate(A15, 38, 41);
  ldrLeft.populate(A14);
  ldrRight.populate(A17);
}


void loop() {  
  for (int i=0; i<4; i++) {
    piezos[i].readInput();
  }
  
  ldrLeft.readInput();
  ldrLeft.sendMIDIData();
  ldrRight.readInput();
  ldrRight.sendMIDIData();

  //Potentiometer to switch channels
  channel = map(analogRead(A20), 0, 1023, 1, 4);
  if (channel != oldChannel) {
    for (int i=0; i<4; i++) {
      piezos[i].channel = channel;
    }
  }  
  oldChannel = channel;
  
  delay(10);
}
