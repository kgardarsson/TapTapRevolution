class LightSensor {
  public:
    int pin;
    int value;
    int channel = 1;
    int mappedValue = 0;
    int oldMappedValue = 0;
    int resetCounter = 0;

    LightSensor();
    void populate(int _pin);
    void readInput();
    int returnValue();
    void sendMIDIData();
};

LightSensor::LightSensor() {
  
}

void LightSensor::populate(int _pin) {
  pin = _pin;
}

void LightSensor::readInput() {
  
  value = analogRead(pin);

  /*
  if (value > peak) {
    peak = value;
  } else if (value < trough) {
    trough = value;
  }
  //reset peak every 5 minutes to account for dimming or brightening outside (sunset, sunrise)
  resetCounter++;
  if (resetCounter == 30000) {
    peak = trough = 300;
    resetCounter = 0;
  }
  */
  
}

void LightSensor::sendMIDIData() {
  mappedValue = constrain(map(value, 1050, 850, 60, 127), 60, 127);
  if (oldMappedValue != mappedValue) {
    usbMIDI.sendControlChange(1,mappedValue,5);
  }
  oldMappedValue = mappedValue;
}

int LightSensor::returnValue() {
  return value;
}
