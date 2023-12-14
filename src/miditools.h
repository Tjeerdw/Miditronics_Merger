#ifndef MIDITOOLS_H
#define MIDITOOLS_H

#include "Arduino.h"
#include "miditools.h"

class notesMemory{
    public:
        notesMemory(int channel);
        bool isAnythingOn();
        void turnNotesOff();
    private:
        int _channel;
        uint32_t noteMemA, noteMemB, noteMemC, noteMemD; //lsb of A is note 0, MSB of D is note 127
};

#endif