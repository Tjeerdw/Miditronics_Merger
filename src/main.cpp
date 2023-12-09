//  This example code is in the public domain.
//  Original Merger code belongs to https://github.com/Deftaudio 

#include <MIDI.h>
//#include <USBHost_t36.h> // access to USB MIDI devices (plugged into 2nd USB port)

#define koppelsChannel 10

bool reactToKoppels = false;


int koppels[15][4] = {
// Midi Value, enabled, note source ch, note destination ch
  {1,0,1,2}, // I+II
  {2,0,1,3}, // I+III
  {3,0,1,4}, // I+IV
  {7,0,2,3}, // II+III
  {8,0,2,4}, // II+IV
  {11,0,3,4}, // III+IV
  {20,0,1,5}, // I+V
  {21,0,2,5}, // II+V
  {22,0,3,5}, // III+V
  {23,0,3,5}, // IV+V
  {24,0,6,1}, // P+I
  {25,0,6,2}, // P+II  
  {26,0,6,3}, // P+III
  {27,0,6,4}, // P+IV
  {28,0,6,2}, // P+II
};

// Create the Serial MIDI ports
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, MIDI1);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial2, MIDI2);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial3, MIDI3);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial4, MIDI4);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial5, MIDI5);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial6, MIDI6);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial7, MIDI7);
MIDI_CREATE_INSTANCE(HardwareSerial, Serial8, MIDI8);
//MIDI_CREATE_INSTANCE(usb_serial_class, Serial, MIDIUSB);

// A variable to know how long the LED has been turned on
elapsedMillis ledOnMillis;

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT); // LED pin
  MIDI1.begin(MIDI_CHANNEL_OMNI);
  MIDI2.begin(MIDI_CHANNEL_OMNI);
  MIDI3.begin(MIDI_CHANNEL_OMNI);
  MIDI4.begin(MIDI_CHANNEL_OMNI);
  MIDI5.begin(MIDI_CHANNEL_OMNI);
  MIDI6.begin(MIDI_CHANNEL_OMNI);
  MIDI7.begin(MIDI_CHANNEL_OMNI);
  MIDI8.begin(MIDI_CHANNEL_OMNI);  //output
  MIDI1.turnThruOff();
  MIDI2.turnThruOff();
  MIDI3.turnThruOff();
  MIDI4.turnThruOff();
  MIDI5.turnThruOff();
  MIDI6.turnThruOff();
  MIDI7.turnThruOff();
  MIDI8.turnThruOff();
  
  digitalWriteFast(13, HIGH); // LED on
  delay(500);
  digitalWriteFast(13, LOW);

}

void loop() {
  bool activity = false;
 

  if (MIDI1.read()) {
    // get a MIDI IN1 (Serial) message
    midi::MidiType type = MIDI1.getType();
    midi::Channel channel = MIDI1.getChannel();
    byte data1 = MIDI1.getData1();
    byte data2 = MIDI1.getData2();

    if (type != midi::SystemExclusive) {
      MIDI8.send(type, data1, data2, channel);
      //MIDIUSB.send(type, data1, data2, channel);
      if (reactToKoppels) {
        if (type == midi::NoteOff ||type == midi::NoteOn){
          //iterate though koppel, if source channel &&enable, send to destination channel
        }
        if (type == midi::ControlChange && channel == koppelsChannel){
          //iterate through koppel, look foor data 2 value, then turn on 80 or off 81
        }
      }
    }   
    activity = true;
  }

  if (MIDI2.read()) {
    // get a MIDI IN2 (Serial) message
    midi::MidiType type = MIDI2.getType();
    midi::Channel channel = MIDI2.getChannel();
    byte data1 = MIDI2.getData1();
    byte data2 = MIDI2.getData2();

    if (type != midi::SystemExclusive) {
      MIDI8.send(type, data1, data2, channel);    
    }   
    activity = true;
  }

  if (MIDI3.read()) {
    // get a MIDI IN1 (Serial) message
    midi::MidiType type = MIDI3.getType();
    midi::Channel channel = MIDI3.getChannel();
    byte data1 = MIDI3.getData1();
    byte data2 = MIDI3.getData2();

    if (type != midi::SystemExclusive) {
      MIDI8.send(type, data1, data2, channel);    
    }   
    activity = true;
  }

  if (MIDI4.read()) {
    // get a MIDI IN1 (Serial) message
    midi::MidiType type = MIDI4.getType();
    midi::Channel channel = MIDI4.getChannel();
    byte data1 = MIDI4.getData1();
    byte data2 = MIDI4.getData2();

    if (type != midi::SystemExclusive) {
      MIDI8.send(type, data1, data2, channel);    
    }   
    activity = true;
  }

  if (MIDI5.read()) {
    // get a MIDI IN1 (Serial) message
    midi::MidiType type = MIDI5.getType();
    midi::Channel channel = MIDI5.getChannel();
    byte data1 = MIDI5.getData1();
    byte data2 = MIDI5.getData2();

   if (type != midi::SystemExclusive) {
      MIDI8.send(type, data1, data2, channel);    
    }   
    activity = true;
  }

  if (MIDI6.read()) {
    // get a MIDI IN1 (Serial) message
    midi::MidiType type = MIDI6.getType();
    midi::Channel channel = MIDI6.getChannel();
    byte data1 = MIDI6.getData1();
    byte data2 = MIDI6.getData2();

   if (type != midi::SystemExclusive) {
      MIDI8.send(type, data1, data2, channel);    
    }   
    activity = true;
  }

    if (MIDI7.read()) {
    // get a MIDI IN1 (Serial) message
    midi::MidiType type = MIDI7.getType();
    midi::Channel channel = MIDI7.getChannel();
    byte data1 = MIDI7.getData1();
    byte data2 = MIDI7.getData2();

    if (type != midi::SystemExclusive) {
      MIDI8.send(type, data1, data2, channel);    
    }   
    activity = true;
  }

  // blink the LED when any activity has happened
  if (activity) {
    digitalWriteFast(13, HIGH); // LED on
    ledOnMillis = 0;
  }
  if (ledOnMillis > 15) {
    digitalWriteFast(13, LOW);  // LED off
  }

}
