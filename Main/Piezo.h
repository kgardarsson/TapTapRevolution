class Piezo {
  public:
    int pin;
    int led;
    int value;
    int brightnessValue = 0;
    int MIDINote;
    int channel = 1;
    const int thresholdMin = 60;
    boolean noteIsOn = false;

    Piezo();
    void populate(int _pin, int _led, int _MIDINote);
    void readInput();
    int returnValue();
};

Piezo::Piezo() {
  
}

void Piezo::populate(int _pin, int _led, int _MIDINote) {
  pin = _pin;
  led = _led;
  MIDINote = _MIDINote;
}

void Piezo::readInput() {
  value = analogRead(pin);
  if (value >= thresholdMin && !noteIsOn) {
  //if (value >= thresholdMin) {
    usbMIDI.sendNoteOn(MIDINote, brightnessValue/2, channel);
    noteIsOn = true;
    int mappedValue = map(value, 0, 1023, 0, 255);
    if (brightnessValue < mappedValue) {
      brightnessValue = mappedValue;
      analogWrite(led, brightnessValue);
    }
  } else if (noteIsOn) {
    usbMIDI.sendNoteOff(MIDINote, brightnessValue/2, channel);
    noteIsOn = false;
  }
  if (brightnessValue > 0) {
    brightnessValue -= 10;
    analogWrite(led, brightnessValue);
  }
}  

int Piezo::returnValue() {
  return value;
}
