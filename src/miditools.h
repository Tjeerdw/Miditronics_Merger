#ifndef MIDITOOLS_H
#define MIDITOOLS_H

#include "Arduino.h"
#include "MIDI.h"
#include "miditools.h"


class KoppelUnit{
    public:
        KoppelUnit(MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>>& midiOutPort);
        void handleKoppels(midi::MidiType type,  midi::Channel channel, byte data1, byte data2);
        bool reactToKoppels;

    private:
        MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>>& _midiOutPort;
        uint32_t notesMem [6][128]; //6 organs, 128 notes each, 32 bits for sources each
        int koppelList[15][4] =
        {
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
            {23,0,4,5}, // IV+V
            {24,0,6,1}, // P+I
            {25,0,6,2}, // P+II  
            {26,0,6,3}, // P+III
            {27,0,6,4}, // P+IV
            {28,0,6,2}, // P+II 
        };
        int g_KoppelRows;
       
};

#endif