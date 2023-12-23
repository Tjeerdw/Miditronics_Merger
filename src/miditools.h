#ifndef MIDITOOLS_H
#define MIDITOOLS_H

#include "Arduino.h"
#include "MIDI.h"
#include "miditools.h"


class KoppelUnit{
    public:
        KoppelUnit(MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>>& midiOutPort);
        void handleKoppels(midi::MidiType type,  midi::Channel channel, byte data1, byte data2, bool sendToUSB);
        bool reactToKoppels;

    private:
        MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>>& _midiOutPort;
        uint32_t notesMem [6][128]; //6 organs, 128 notes each, 32 bits for sources each
        int koppelList[21][5] =
        {
            // Midi Value, enabled, note source ch, note destination ch, noteMembit
            {58,0,1,1,1}, // I+I
            {24,0,6,1,2}, // P+I
            {59,0,2,2,1}, // II+II
            {1 ,0,1,2,2}, // I+II
            {25,0,6,2,3}, // P+II  
            {60,0,3,3,1}, // III+III
            {2 ,0,1,3,2}, // I+III
            {7 ,0,2,3,3}, // II+III
            {26,0,6,3,4}, // P+III
            {61,0,4,4,1}, // IV+IV
            {3 ,0,1,4,2}, // I+IV
            {8 ,0,2,4,3}, // II+IV
            {11,0,3,4,4}, // III+IV
            {27,0,6,4,5}, // P+IV
            {62,0,5,5,1}, // V+V
            {20,0,1,5,2}, // I+V
            {21,0,2,5,3}, // II+V
            {22,0,3,5,4}, // III+V
            {29,0,4,5,5}, // IV+V
            {28,0,6,5,6}, // P+V 
            {63,0,6,6,1}, // P+P
        };
        int g_KoppelRows;
       
};

#endif