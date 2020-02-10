#include "Piezo.h"
#include "LightSensor.h"
// jj

Piezo piezos[8];
LightSensor ldr;
int oldChannel;
int channel;
int lightValue;

void setup() {
  Serial.begin(115200);
  while (!Serial && millis() < 2500) /* wait for serial monitor */ ;
  piezos[0].populate(A15, 35, 36); // COORECT 1st one
  piezos[1].populate(A19, 36, 38); 
  piezos[2].populate(A14, 30, 40); //CORRECT 3rd one
  piezos[3].populate(A18, 29, 41);
  ldr.populate(A12); // CORRECT Light Sensor
}


void loop() {  
  for (int i=0; i<4; i++) {
    piezos[i].readInput();
  }
  
  ldr.readInput();
  ldr.sendMIDIData();

  //Potentiometer to switch channels
  channel = map(analogRead(A13), 0, 1023, 1, 4); // CORRECT potentiometer
  if (channel != oldChannel) {
    for (int i=0; i<4; i++) {
      piezos[i].channel = channel;
    }
  }  
  oldChannel = channel;
  
  delay(10);
}
