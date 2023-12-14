#include "Arduino.h"
#include "miditools.h"

notesMemory::notesMemory(int channel){
    _channel = channel;
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

