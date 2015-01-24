#ifndef MIDI_EVENT_H
#define MIDI_EVENT_H

#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

namespace Midi {

enum MidiMessageType {Midi = 0, MidiNoteOff = 0x8, MidiNoteOn, MidiPolyAftertouch, 
                      MidiControlChange, MidiProgramChange,    MidiChannelAftertouch, 
                      MidiPitchWheel,    MidiMetaEvent = 0xFF, MidiSysex1 = 0xF0, MidiSysex2 = 0xF7};


enum MidiMetaType {MetaSequenceNumber = 0x0, MetaTextEvent = 0x1,      MetaCopyright = 0x2,
                   MetaTrackName  = 0x3,     MetaInstrumentName = 0x4, MetaLyricText = 0x5,
                   MetaMarkerText = 0x6,     MetaCuePoint = 0x7,       MetaChannelPrefixAssignment = 0x20,
                   MetaEndOfTrack = 0x2F,    MetaTempoSetting = 0x51,  MetaSMPTEOffset = 0x54,
                   MetaTimeSignature = 0x58, MetaKeySignature = 0x59,  MetaSequenceSpecific = 0x7F};

/***
 *   Spec:
 *   MidiTrackEvent = <delta_time (Variable)> + <MidiEvent> | <MetaEvent> | <SysexEvent>
 *   MidiEvent = <MidiMessageType (4 bits)>  + <channel (4 bits)> + <parameter1 (1 byte)> <parameter2 (1 byte)>
 *   MetaEvent = 0xFF + <MidiMetaType> + <size (Variable)> + <data>
 *   SysexEvent = 0xF0 + <data> + 0xF7  -or- 
 *   SysexEvent = 0xF7 + <data> 0xF7
 ***/

class Event {
    private:
    unsigned int  m_delta;
    unsigned int  m_size;
    unsigned int  m_data_size;
    unsigned char m_status;
    unsigned char m_meta_type;
    unsigned char m_parameter1;
    unsigned char m_parameter2;
    void *m_data;

    public:
    Event();
    Event(int delta, int status, int parameter1, int parameter2);
    void init_midi(int delta, int status, int parameter1, int parameter2);
    void init_from_file(FILE *fp, unsigned char last_status);
    ~Event();

    //  Some easy inline functions
    static bool is_status_byte(unsigned char byte) { return ((byte & 0x80) >> 7) == 1; } 
    unsigned int delta() const { return m_delta; }
    unsigned char status() const { return m_status; }
    unsigned int bytes_read() const { return m_size; }
    unsigned char parameter1() const { return m_parameter1; }
    unsigned char parameter2() const { return m_parameter2; }
    int message_type() const { return (m_status &0xF0) >> 4; }
    int channel() const { return (m_status &0xF); }
    void *sysex_data() const { return m_data; }

    void print(){
        printf("%x, ", m_delta);
        switch(m_delta){
            case MidiMetaEvent:
                printf("Meta: 0xFF, %x, <size>, <data>\n", m_meta_type);
                break;
            case MidiSysex1:
                printf("Sysex1: 0xF0, <data>\n");
                break;
            case MidiSysex2:
                printf("Sysex2: 0xF7, <data>\n");
                break;
            default:
                printf("Event: %x, %x, %x\n", m_status, m_parameter1, m_parameter2 );
                break;
        }
    }
    /*
    void print(void){ 
        //if(m_status < 0xf0){ return ; } 
        printf("{\n"); 
        printf("Delta: 0x%x\n", m_delta); 
        printf("Bytes Consumed: %d\n", m_size); 
        printf("Status: 0x%x\n", m_status); 
        switch(m_status){ 
            case 0xFF: 
                printf("Meta Type: 0x%x\n", m_meta_type); 
                printf("Meta Data Size : %d\n", m_data_size); 
                break; 
            case 0xF0: 
            case 0xF7: 
                printf("Sysex Data Size : %d\n", m_data_size); 
                break; 
            default: 
                printf("Parameter 1: 0x%x\n", m_parameter1); 
                printf("Parameter 2: 0x%x\n", m_parameter2); 
        } 
        if(m_data){ 
            printf("Data: "); 
            for(int i = 0; i < m_data_size; i++){ 
                    printf("0x%x ", ((unsigned char*)m_data)[i]); 
            } 
            printf("\n"); 
            printf("Data (String): \""); 
            for(int i = 0; i < m_data_size; i++){ 
                printf("%c", ((unsigned char*)m_data)[i]); 
            } 
            printf("\"\n"); 
        } 
        printf("}\n\n"); 
    }
    */
};

}

#endif
