#include "miditools.h"

notesMemory::notesMemory( MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>>& midiOutPort)
    :  _midiOutPort(midiOutPort)
{
    //noteMemA = 0;
    //noteMemB = 0;
    //noteMemC = 0;
    //noteMemD = 0;
}


bool notesMemory::isAnythingOn(int channel){
    if(noteMemA[channel]==0 && noteMemB[channel]==0 && noteMemC[channel]==0 && noteMemD[channel]==0){
        return false;
    }
    else{
        return true;
    }
}

void notesMemory::koppelOnNotes(int sourceChannel, int DestinationChannel){
    //go through source channelmem and send note on to dest channel
    //also send to memory
}

void notesMemory::koppelOffNotes(int Destinationchannel){
    //
}

void notesMemory::putNoteInMemory(int channel, int note, bool fromKoppel, bool noteOn){

}



