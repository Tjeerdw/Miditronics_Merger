#ifndef MIDITOOLS_H
#define MIDITOOLS_H

#include "Arduino.h"
#include "MIDI.h"
#include "miditools.h"

//#define SERIALDEBUG
#define useUSBMIDI

#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))
#define koppelsChannel 10
#define registerChannelA 8
#define registerChannelB 9

#define KL_Value 0
#define KL_Enabled 1
#define KL_Source 2
#define KL_Destination 3
#define KL_KoppelBit 4
#define KL_Transpose

class KoppelUnit{
    public:
        KoppelUnit(MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>>& midiOutPort);
        void handleKoppels(midi::MidiType type,  midi::Channel channel, byte data1, byte data2, bool sendToUSB);
        void koppelNoteOn(midi::MidiType type, byte note, byte velocity, int destinationchannel,bool sendToUSB, int koppelListIndex);
        void koppelNoteOff(midi::MidiType type, byte note, byte velocity, int destinationchannel, bool sendToUSB,int koppelListIndex);
        void printNotesMem(int channel);

    private:
        MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>>& _midiOutPort;
        uint32_t notesMem [7][128]; //6 organs, 128 notes each, 32 bits for sources each, organ 0 not used
        bool reactToKoppels;
        int koppelList[24][6] =
        {
            // Midi Value, enabled, note source ch, note destination ch, noteMembit
            {58,1,1,1,1,0},   // I+I
            {24,0,6,1,2,0},   // P+I
            {59,1,2,2,1,0},   // II+II
            {1 ,0,1,2,2,0},   // I+II
            {4 ,0,1,2,2,-12}, // I+II 16'
            {25,0,6,2,3,0},   // P+II  
            {60,1,3,3,1,0},   // III+III
            {2 ,0,1,3,2,0},   // I+III
            {6 ,0,1,3,2,-12},   // I+III 16'
            {7 ,0,2,3,3,0},   // II+III
            {9 ,0,2,3,3,-12},   // II+III 16'
            {26,0,6,3,4,0},   // P+III
            {61,1,4,4,1,0},   // IV+IV
            {3 ,0,1,4,2,0},   // I+IV
            {8 ,0,2,4,3,0},   // II+IV
            {11,0,3,4,4,0},   // III+IV
            {27,0,6,4,5,0},   // P+IV
            {62,1,5,5,1,0},   // V+V
            {20,0,1,5,2,0},   // I+V
            {21,0,2,5,3,0},   // II+V
            {22,0,3,5,4,0},   // III+V
            {29,0,4,5,5,0},   // IV+V
            {28,0,6,5,6,0},   // P+V 
            {63,1,6,6,1,0},   // P+P
        };
        int g_KoppelRows;
        int g_NumberOfNotes;
       
};

#endif