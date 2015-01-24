#include "nodes/voice.h"

namespace Nodes {

////
//  
Voice::Voice(const char *name) : Base(name), m_adsr1("Osc 1 ADSR", this), m_busy(false) { 
    m_oscillator1 = new Cosine("Cosine Osc 1");
    m_oscillator1->attach_modulator(&m_adsr1);
}


////
//  Destructor, free inner nodes
Voice::~Voice(){
    delete m_oscillator1;
}


////
//  Process audio for this voice
void Voice::_process(AudioBuffer &audio_buffer){
    m_oscillator1->process(audio_buffer);
}


////
//  Maybe got sysex event from envelope closing
void Voice::sysex_env_closed(Midi::Event &event){
    printf("Voice got sysex1\n");
    //void *addr_ptr = event.sysex_data();
    //m_busy = false;
}


////
//  Process MIDI for this voice
void Voice::midi_callback(Midi::Event &event){
    using namespace Midi;

    switch(event.message_type()){
        case MidiNoteOn:
            m_busy = true;
            m_oscillator1->midi_callback(event);
            m_adsr1.midi_callback(event);
            break;
        case MidiNoteOff:
            m_adsr1.midi_callback(event);
            break;
        case MidiSysex1:
            sysex_env_closed(event);
            break;
    }
}


}
