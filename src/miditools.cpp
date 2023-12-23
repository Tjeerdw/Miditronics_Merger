#include "miditools.h"

KoppelUnit::KoppelUnit( MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>>& midiOutPort)
    :  _midiOutPort(midiOutPort)
{   
    reactToKoppels = true;
    g_KoppelRows = LEN(koppelList);
    g_NumberOfNotes = 128;
}

void KoppelUnit::handleKoppels(midi::MidiType type,  midi::Channel channel, byte data1, byte data2, bool sendToUSB){ //data1 is note and 80/81, data2 is velocity and value
    #ifndef useUSBMIDI
    Serial.printf("type: %d  Channel %d  data1 %d  data2 %d\n",type,channel,data1,data2);
    #endif
    
    if (type == midi::NoteOff ||type == midi::NoteOn){ //note message incoming
        for (int i=0 ; i<g_KoppelRows;i++){ //go through koppelList, find matching source channel and enabled, could be more than one
            if ((koppelList[i][KL_Enabled]==true) && koppelList[i][KL_Source]==channel ){// koppel enabled and has matching source channel
                if(type == midi::NoteOn){
                    koppelNoteOn(data1,data2,koppelList[i][KL_Destination]);
                }
                else if(type == midi::NoteOff){
                    koppelNoteOff(data1,data2,koppelList[i][KL_Destination]);
                }
            } 
        }
    
    }
    else if (type == midi::ControlChange && channel == koppelsChannel){ //koppel message incoming

    for (int i=0 ; i<g_KoppelRows;i++){ //go through koppelList, find matching koppel
            if (koppelList[i][KL_Value]==data2){ //match
                switch(data1) { //koppel on or off
                    case 80: //Koppel aan
                        koppelList[i][KL_Enabled] = 1; //enable matching koppel in koppel mem
                        /*
                        search for 1:1 koppel bits in source channel, "was er al iets aan"
                        if note in desination mem is off "en nog niet aan op de destination"
                            koppelNoteOn() 
                        edit note in destination notesmem
                        */
                        break;
                    case 81: //koppel uit
                        koppelList[i][KL_Enabled] = 0; //disable matching koppel in koppel mem
                        /*
                        search for koppelbits on in destination channel "staat er iets aan dat uit moet"
                        zet deze koppelbits uit
                        If note is now 0
                            koppelNoteOff()
                        */
                        break;
                }
            }
        }
    }
    else if (type == midi::ControlChange && channel == (registerChannelA || registerChannelB)){ //register message incoming
        //just pas through as usual
    }
}

void KoppelUnit::koppelNoteOn(byte note, byte velocity, int destinationchannel){

    /*
    if note in desination mem is off
        send note to desitnation channel 
    else
        don'tsend note
    edit note in destination notesmem

     _midiOutPort.send(type, data1, data2, koppelList[i][3]);
            #ifdef useUSBMIDI
            usbMIDI.send(type, data1, data2, koppels[i][3],0);
            #endif
    */
}

void KoppelUnit::koppelNoteOff(byte note, byte velocity, int destinationchannel){
    /*
    edit note in destination notesmem
    if deistation mem=0
        send note off
    */
}




