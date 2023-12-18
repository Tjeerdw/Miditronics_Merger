#include "Arduino.h"
#include "miditools.h"

notesMemory::notesMemory(int channel, MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>>& midiOutPort)
    : _channel(channel), _midiOutPort(midiOutPort)
{
    noteMemA = 0;
    noteMemB = 0;
    noteMemC = 0;
    noteMemD = 0;
}


bool notesMemory::isAnythingOn(){
    if(noteMemA==0 && noteMemB==0 && noteMemC==0 && noteMemD==0){
        return false;
    }
    else{
        return true;
    }
}
void notesMemory::turnNotesOff(){
}

