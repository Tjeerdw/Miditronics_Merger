#ifndef MIDITOOLS_H
#define MIDITOOLS_H

#include "Arduino.h"
#include "MIDI.h"
#include "miditools.h"


class notesMemory{
    public:
        notesMemory(int channel, MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>>& midiOutPort);
        bool isAnythingOn();
        void turnNotesOff();
    private:
        int _channel;
        MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>>& _midiOutPort;
        uint32_t noteMemA, noteMemB, noteMemC, noteMemD; //lsb of A is note 0, MSB of D is note 127
};

#endif