#include "miditools.h"

#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))
#define koppelsChannel 10
#define registerChannelA 8
#define registerChannelB 9


KoppelUnit::KoppelUnit( MIDI_NAMESPACE::MidiInterface<MIDI_NAMESPACE::SerialMIDI<HardwareSerial>>& midiOutPort)
    :  _midiOutPort(midiOutPort)
{   
    reactToKoppels = true;
    g_KoppelRows = LEN(koppelList);
}


void KoppelUnit::handleKoppels(midi::MidiType type,  midi::Channel channel, byte data1, byte data2, bool sendToUSB){
    #ifndef useUSBMIDI
    Serial.printf("type: %d  Channel %d  data1 %d  data2 %d\n",type,channel,data1,data2);
    #endif
    
    if (type == midi::NoteOff ||type == midi::NoteOn){ //note message incoming
        /*
        go through koppelList, find matching source channel and enabled
            if note on
                if note in desination mem is off
                    send note to desitnation channel 
                else
                    don'tsend note
                edit note in destination notesmem
                
             if note off
                edit note in destination notesmem
                if deistation mem=0
                    send note off
                */
    }
    else if (type == midi::ControlChange && channel == koppelsChannel){ //koppel message incoming
    
    }
    else if ((type == midi::ControlChange && channel == (registerChannelA || registerChannelB)){ //register message incoming
    
    }
    
    
    if (type == midi::NoteOff ||type == midi::NoteOn){ // if notes, check if there is a matching couple that is enabled
        for (int i=0 ; i<g_KoppelRows;i++){
            //Serial.printf("%d,%d,%d,%d\n",koppels[i][0],koppels[i][1],koppels[i][2],koppels[i][3]); //print out koppel array
            if ((koppelList[i][1]==true) && koppelList[i][2]==channel ){// koppel enabled and has matching source channel
            _midiOutPort.send(type, data1, data2, koppelList[i][3]);
            #ifdef useUSBMIDI
            usbMIDI.send(type, data1, data2, koppels[i][3],0);
            #endif
            //todo:turn note on/off in midikoppelmem
            } 
        }
        //turn note on/off in approprate midimem
    }
    if (type == midi::ControlChange && channel == koppelsChannel){
        switch(data1) {//data1 is CC#, data 2 is Value
        case 80: //Koppel aan
            for (int i=0 ; i<g_KoppelRows;i++){
            if (koppelList[i][0]==data2){//find which koppel
                koppelList[i][1] = 1; //enable matching koppel in koppel mem
                //TODO:turn on current notes from koppelSourcemem to koppelDestination
            }
            }
            break;
        case 81: //koppel uit
            for (int i=0 ; i<g_KoppelRows;i++){
            if (koppelList[i][0]==data2){ //find which koppel
                koppelList[i][1] = 0;  //disable matching koppel in koppel mem"
                //TODO:turn off current notes in destinationkoppelmem
            }
            }
            break;
        default:
            break;
        }
    }
}



