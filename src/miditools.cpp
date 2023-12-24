#include "miditools.h"

KoppelUnit::KoppelUnit( MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>>& midiOutPort)
    :  _midiOutPort(midiOutPort)
{   
    reactToKoppels = true;
    g_KoppelRows = LEN(koppelList);
    g_NumberOfNotes = 128;
}

void KoppelUnit::handleKoppels(midi::MidiType type,  midi::Channel channel, byte data1, byte data2, bool sendToUSB){ //data1 is note and 80/81, data2 is velocity and value
    #ifdef SERIALDEBUG
    Serial.printf("HandleKoppel IN: type: %d  Channel %d  data1 %d  data2 %d\n",type,channel,data1,data2);
    #endif
    
    if (type == midi::NoteOff ||type == midi::NoteOn){ //note message incoming
        for (int i=0 ; i<g_KoppelRows;i++){ //go through koppelList, find matching source channel and enabled, could be more than one
            if ((koppelList[i][KL_Enabled]==true) && koppelList[i][KL_Source]==channel ){// koppel enabled and has matching source channel
                if(type == midi::NoteOn){
                    koppelNoteOn(type, data1,data2,koppelList[i][KL_Destination],sendToUSB,i);
                }
                else if(type == midi::NoteOff){
                    koppelNoteOff(type, data1,data2,koppelList[i][KL_Destination],sendToUSB,i);
                }
            } 
        }
    
    }
    else if (type == midi::ControlChange && channel == koppelsChannel){ //koppel message incoming

    for (int i=0 ; i<g_KoppelRows;i++){ //go through koppelList, find matching koppel
            if (koppelList[i][KL_Value]==data2){ //match
                int KL_sourceChannel = koppelList[i][KL_Source];
                int KL_destinationChannel = koppelList[i][KL_Destination];
                int KL_koppelbitje = koppelList[i][KL_KoppelBit];
                switch(data1) { //koppel on or off
                    case 80: //Koppel aan
                        koppelList[i][KL_Enabled] = 1; //enable matching koppel in koppel mem
                        for ( int j=0 ; j<g_NumberOfNotes ; j++){ //go though all notes in sourcechannel
                            if (notesMem[KL_sourceChannel][j] & 1<<1){ //search for 1:1 koppel bits in source channel, "was er al iets aan"
                                koppelNoteOn(midi::NoteOn,j,data2,KL_destinationChannel, sendToUSB, i); 
                            }
                        }
                        
                        break;
                    case 81: //koppel uit
                        koppelList[i][KL_Enabled] = 0; //disable matching koppel in koppel mem
                        for ( int j=0 ; j<g_NumberOfNotes ; j++){ //go though all notes in destination channel
                            if (notesMem[KL_destinationChannel][j] & 1<<KL_koppelbitje){  //search for koppelbits on in destination channel "staat er iets aan dat uit moet
                                koppelNoteOff(midi::NoteOff,j,data2,KL_destinationChannel, sendToUSB, i); 
                            }
                        }
                        break;
                }
            }
        }
    }
    else if (type == midi::ControlChange && channel == (registerChannelA || registerChannelB)){ //register message incoming, just pass through
        
    _midiOutPort.send(type, data1, data2,channel); // send note to desitnation channel 
        #ifdef useUSBMIDI
        if (sendToUSB){
            usbMIDI.send(type, data1, data2,channel,0); //also to usb
        }
        #endif
    }
}

void KoppelUnit::koppelNoteOn(midi::MidiType type, byte note, byte velocity, int destinationchannel, bool sendToUSB, int koppelListIndex){
    #ifdef SERIALDEBUG
    Serial.printf("koppelNoteOn OUT: type: %d  Channel %d  data1 %d  data2 %d\n",type,destinationchannel,note,velocity);
    printNotesMem(destinationchannel);
    #endif
    if(notesMem[destinationchannel][note]==0){     //if note in desination mem is off
        _midiOutPort.send(type, note, velocity,destinationchannel); // send note to desitnation channel 
        #ifdef useUSBMIDI
        if (sendToUSB){
            usbMIDI.send(type, note, velocity,destinationchannel,0); //also to usb
        }
        #endif
    }
    notesMem[destinationchannel][note] |= 1<<koppelList[koppelListIndex][KL_KoppelBit]; //  edit note in destination notesmem
}

void KoppelUnit::koppelNoteOff(midi::MidiType type, byte note, byte velocity, int destinationchannel, bool sendToUSB, int koppelListIndex){
    #ifdef SERIALDEBUG
    Serial.printf("koppelNoteOff OUT: type: %d  Channel %d  data1 %d  data2 %d\n",type,destinationchannel,note,velocity);
    #endif
    notesMem[destinationchannel][note] &= ~(1<< koppelList[koppelListIndex][KL_KoppelBit]); //  edit note in destination notesmem
    if(notesMem[destinationchannel][note]==0){
        _midiOutPort.send(type, note, velocity,destinationchannel); // send note to desitnation channel 
        #ifdef useUSBMIDI
        if (sendToUSB){
            usbMIDI.send(type, note, velocity,destinationchannel,0); //also to usb
        }
        #endif
    }
}

void KoppelUnit::printNotesMem(int channel){
    Serial.printf("Notesmem Ch%d: ", channel);
    for ( int j=0 ; j<g_NumberOfNotes ; j++){
        Serial.print(notesMem[channel][j]);
        Serial.print(",");
    }
    Serial.println();
}




